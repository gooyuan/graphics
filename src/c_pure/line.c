

/**
 * 画直线
 * Bresenham
 * 直接有两种趋势, 即 斜率在 0~1之间的方向, <0 && >1 范围的方向 
 * 按夹角算就是 0~45, 45~360 
 */
#include "line.h"

#define PI 3.14159265359f
#define W 512
#define H 512

static unsigned char img[W * H * 3];

void setpixel(int x, int y) {
    unsigned char *p = img + (y * W + x) * 3;
    // 线的颜色为黑色
    p[0] = p[1] = p[2] = 255;
}

/**
 * milo yip 简易实现
 * 这比维基上的要精炼很多
 * x, y 方向上同时积err
 */
void optimize_bresenham(int x0, int y0, int x1, int y1) {
    // sx, sy 代表什么?  步进量
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    // 斜率问题: dx > dy, 斜率 0~1, 否则 >1
    // 除以2 是过一半 步进一次
    // 斜率大于1, err 从 -dy 开始积
    int err = (dx > dy ? dx : -dy) / 2;

    while (setpixel(x0, y0), x0 != x1 || y0 != y1) {
        int e2 = err;
        // 与初始化err的时候反着来, 这样的思想很精妙, 但是想不明白, 隐约觉着很有道理
        // 这两个比较顺序调换一下, 结果会不会不一样? 不会, 这是两个方向同时的
        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }
        // 斜率 小于1
        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}

char *drawLineWithSimpleBresenham() {
    // 底色初始为了黑色
    memset(img, 0, sizeof(img));

    // 圆心
    float cx = W * 0.5f - 0.5f, cy = H * 0.5f - 0.5f;
    // 64条直接幅度
    float dt = 2.0f * PI / 64;
    for (int j = 0; j < 5; j++) {
        float r1 = fminf(W, H) * (j + 0.5f) * 0.085f;
        float r2 = fminf(W, H) * (j + 1.5f) * 0.085f;
        // 每一层错位 PI/64;
        float t = j * PI / 64;
        for (int i = 1; i <= 64; i++, t += dt) {
            float ct = cosf(t), st = sinf(t);
            optimize_bresenham((int) (cx + r1 * ct), (int) (cy + r1 * st), (int) (cx + r2 * ct), (int) (cy + r2 * st));
        }
    }
    // svpng(fopen("line_bresenham.png", "wb"), W, H, img, 0);
    return img;
}

/**
 * 判断一点(px, py) 是否在胶囊体(ax,ay) (bx,by)之中
 * 胶囊体, 给定一个线段 L, 所有到线段L的距离为了 r 的点的集合
 * 检测两个胶囊体是否发生碰撞, 即检测两条线段 L1, L2 的最短距离 d 是否大于 L1, L2 的半径 r1,r2 之和
 * 检测一个点是否在胶囊体内, 该点到线段的距离与 r 比较
 */
int capsule(float px, float py, float ax, float ay, float bx, float by, float r) {
    // 判断胶囊体
    float pax = px - ax, pay = py - ay, bax = bx - ax, bay = by - ay;
    // 这一步求什么? 比例? 这样怎么就能将距离求出来了呢, 此步是将h限制在了 0~1 之间
    // 是向量运算: h是 p点到向量ba垂线交点的分向量比例
    // 向量点乘公式: |a|*|b|*cos(x) 向量相乘, 也可转化了矩阵相乘
    // 点到向量距离的向量公式: a,b都为向量
    // (a*b)/(|b|^2) * b
    float h = fmaxf(fminf((pax * bax + pay * bay) / (bax * bax + bay * bay), 1.0f), 0.0f);
    // dx,dy就是垂向量的坐标
    float dx = pax - bax * h, dy = pay - bay * h;
    //    float dx = pax - bax * h, dy = pay - bay * h;

    // false:0, true:1, 非零即真, 但是编译器将非零值设置为1,
    // 非零即真, 也是为了在编码上有更大的弹性, 其实bool值用0,1表示足够了
    return dx * dx + dy * dy < r * r;
}

/**
 * SDF: Signed Distance Field, 符号距离场
 * @return 点距线段的距离差
 */
float capsuleSDF(float px, float py, float ax, float ay, float bx, float by, float r) {
    float pax = px - ax, pay = py - ay, bax = bx - ax, bay = by - ay;
    float h = fmaxf(fminf((pax * bax + pay * bay) / (bax * bax + bay * bay), 1.0f), 0.0f);
    float dx = pax - bax * h, dy = pay - bay * h;

    //sdf改进
    return r - sqrtf(dx * dx + dy * dy);
}

/**
 * 对坐标(x,y)进行采样
 * 这里所谓采样的意思就是按胶囊体的面积来确认线的宽度, 将每层圆环的画线的判断抽象出来
 * @return 是否在绘画区域内
 */
float sample(float x, float y) {

    float s = 0.0f, cx = W * 0.5f, cy = H * 0.5f;
    float dt = 2.0f * PI / 64;
    for (int j = 0; j < 5; j++) {
        // 胶囊体半径控制线宽
        float r1 = fminf(W, H) * (j + 0.5f) * 0.085f;
        float r2 = fminf(W, H) * (j + 1.5f) * 0.085f;
        // 每一层错位 PI/64;
        float t = j * PI / 64, r = (j + 1) * 0.5f;
        for (int i = 1; i <= 64; i++, t += dt) {
            float ct = cosf(t), st = sinf(t);
            // 这一步的逻辑是啥意思, s, 一旦变为1.0f, 就一直是1.0f了, 那么capsule的检测就没有意义了
            // s = fmaxf(s, capsule(x, y, cx + r1 * ct, cy - r1 * st, cx + r2 * ct, cy - r2 * st, r) ? 1.0f : 0.0f);
            // 去掉之后只有一个环,一个方向有线
            s = capsule(x, y, cx + r1 * ct, cy - r1 * st, cx + r2 * ct, cy - r2 * st, r) ? 1.0f : 0.0f;
            // 如果capsule检测没有意义了, 那不也是意味着, capsule为真后, 直接返回, 效率更高
            if (s)
                return s;
            // 到此验证, 说明capsule验证点是否在某个胶囊体中, sample函数中验证图片的每个点是否在要画的所有方向上点的胶囊体中
            // 这样效率更高一点
        }
    }
    return s;
}

/**
 * 此算法是为了线的宽度可控, 算法还是 bresenham
 */
char *drawLineWithSample() {
    // 底色初始为了白色
    memset(img, 255, sizeof(img));
    unsigned char *p = img;
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++, p += 3) {
            // 1.0 - sample(x,y) 是颜色确认的方法, 非黑即白
            // p[0] = p[1] = p[2] = (unsigned char) ((1.0f - sample(x, y)) * 255);
            // 继而可以优化成彩色的
            if (sample(x, y)) {
                p[0] = (unsigned char) (x % 255);
                p[1] = (unsigned char) (y % 255);
                p[2] = (unsigned char) ((x + y) % 255);
            }
        }
    }
    return img;
}

/**
 * 以每个像素为中心, 5x5栅格采样, 使用采样累积/栅格面积
 */
char *drawLineWithAntiAliasing() {
    // 底色初始为了黑色
    memset(img, 0, sizeof(img));
    unsigned char *p = img;
    int sh = 5, sw = 5;
    float sum = 0.0f;
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++, p += 3) {
            sum = 0.0f;
            for (int a = -sh / 2; a < sh / 2; a++) {
                for (int b = -sw / 2; b < sw / 2; b++) {
                    sum += sample(x + (float) b / sw, y + (float) a / sh);
                }
            }
            if (sum) {
                float s = sum / (sw * sh);
                // p[0] = p[1] = p[2] = (unsigned char)(255 * s);
                p[0] = (unsigned char) ((x % 255) * s);
                p[1] = (unsigned char) ((y % 255) * s);
                p[2] = (unsigned char) (((x + y) % 255) * s);
            }
        }
    }
    return img;
}

/**
 * 对坐标(x,y)进行采样
 * 这里所谓采样的意思就是按胶囊体的面积来确认线的宽度, 将每层圆环的画线的判断抽象出来
 * @return sdf值, 用来作颜色比例
 */
float sampleSDF(float x, float y) {
    float s = 0.0f, cx = W * 0.5f, cy = H * 0.5f;
    float dt = 2.0f * PI / 64.0f;
    for (int j = 0; j < 5; j++) {
        float r1 = fminf(W, H) * (j + 0.5f) * 0.085f;
        float r2 = fminf(W, H) * (j + 1.5f) * 0.085f;
        float t = j * PI / 64, r = (j + 1) * 0.5f;
        for (int i = 1; i <= 64; i++, t += dt) {
            float ct = cosf(t), st = sinf(t);
            // sdf 中心点使用0.5 opacity
            // 这里经历了两次替换, capsuleSDF 返回的是点到线段的距离差, >0 在外面, 小于0是在内部, 等于0是在绘画点上
            // r的范围在 0~2.5 之间, 每一层线的宽度,
            // s 的范围限定在 0~1 的范围用以补全色值
            // capsuleSDF返回值 都是在胶囊体内
            s = fmaxf(s, fminf(capsuleSDF(x, y, cx + r1 * ct, cy - r1 * st, cx + r2 * ct, cy - r2 * st, r), 1.0f));
            // 加了这行代码, 是少算了几次
            if (s)
                return s;
        }
    }
    return s;
}

/**
 * 较于super sample, 效率更高一些, 只做一次sdf运算
 */
char *drawLineWithSDF() {
    memset(img, 0, sizeof(img));
    // 底色初始为了黑色
    unsigned char *p = img;
    float s = 0.0f;
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++, p += 3) {
            s = sampleSDF(x, y);
            // p[0] = p[1] = p[2] = (unsigned char)(255 * s);
            p[0] = (unsigned char) ((x % 255) * s);
            p[1] = (unsigned char) ((y % 255) * s);
            p[2] = (unsigned char) (((x + y) % 255) * s);
        }
    }
    return img;
}

/**
 * 这里就见到了 alpha blend, so exciting
 * 
 */
void alphablend(int x, int y, float alpha, float r, float g, float b) {
    // 当前p的坐标
    unsigned char *p = img + (y * W + x) * 3;
    // 这里没必要再乘以255了吧? 一会换成彩色的试试有没有必要
    // p[0] = (unsigned char)(p[0] * (1-alpha) + r * alpha * 255);
    // p[1] = (unsigned char)(p[1] * (1-alpha) + r * alpha * 255);
    // p[2] = (unsigned char)(p[2] * (1-alpha) + r * alpha * 255);
    p[0] = (unsigned char) (p[0] * (1 - alpha) + r * alpha);
    p[1] = (unsigned char) (p[1] * (1 - alpha) + g * alpha);
    p[2] = (unsigned char) (p[2] * (1 - alpha) + b * alpha);
}

/**
 * 从参数看, 是 capsule 的模型
 * 
 * 实际实现是按此模型求一个外切矩形
 * 减小了计算量, 速度果然快了很多 
 */
void lineSDFAABB(float ax, float ay, float bx, float by, float r) {
    int x0 = (int) floorf(fminf(ax, bx) - r);
    int y0 = (int) floorf(fminf(ay, by) - r);
    int x1 = (int) ceilf(fmaxf(ax, bx) + r);
    int y1 = (int) ceilf(fmaxf(ay, by) + r);

    for (int y = y0; y <= y1; y++) {
        for (int x = x0; x <= x1; x++) {
            alphablend(x, y, fmax(fminf(capsuleSDF(x, y, ax, ay, bx, by, r), 1.0f), 0.0f), 155.0f, 55.0f, 155.0f);
        }
    }
}

/**
 * AABB: anti-aligned bounding box
 */
char *drawLineWithAABBSDF() {
    memset(img, 0, sizeof(img));
    float cx = W * 0.5f, cy = H * 0.5f;
    float DT = 2.0 * PI / 64.0f;
    for (int i = 0; i < 5; i++) {
        float r1 = fminf(W, H) * (i + 0.5f) * 0.085f;
        float r2 = fminf(W, H) * (i + 1.5f) * 0.085f;
        // t是起始角度, r是每一层胶囊体的r
        float t = i * PI / 64.0f, r = (i + 1) * 0.5f;
        for (int j = 0; j <= 64; j++, t += DT) {
            float ct = cosf(t), st = sinf(t);
            lineSDFAABB(cx + r1 * ct, cy + r1 * st, cx + r2 * ct, cy + r2 * st, r);
        }
    }
    return img;
}

unsigned char *drawStitchHeart() {
    memset(img, 0, sizeof(img));
    float cx = W * 0.5f, cy = H * 0.5f;
    float r = fminf(W, H) * 0.45f;
#define S(a, b) lineSDFAABB(cx + r*cosf(a), cy - r * sinf(a), cx + r * cosf(b), cy - r * sinf(b), 0.5f)
    for (int i = 0; i <= 64; i++) {
        float t = i * (0.5 * PI / 64.0f);
        // 下面又是心型曲线的另一种表示方式?
        S(t, t - PI * 0.5f);
        S(t + PI, t + PI * 0.5f);
        S(t, t * 2.0f + PI * 0.5f);
        S(PI - t, PI * 0.5f - t * 2.0f);
        S(PI * 1.5f, PI * 1.5f - t);
        S(PI * 1.5f, PI * 1.5f + t);
    }
    return img;
}
