

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
    // 这一步求什么? 比例?
    float h = fmaxf(fminf((pax * bax + pay * bay) / (bax * bax + bay * bay), 1.0f), 0.0f);
    float dx = pax - bax * h, dy = pay - bay * h;
//    float dx = pax - bax * h, dy = pay - bay * h;
    return dx * dx + dy * dy < r * r;

}

/**
 * 对坐标(x,y)进行采样
 */
float sample(float x, float y) {

    float s = 0.0f, cx = W * 0.5f, cy = H * 0.5f;
    float dt = 2.0f * PI / 64;
    for (int j = 0; j < 5; j++) {
        float r1 = fminf(W, H) * (j + 0.5f) * 0.085f;
        float r2 = fminf(W, H) * (j + 1.5f) * 0.085f;
        // 每一层错位 PI/64;
        float t = j * PI / 64, r = (j + 1) * 0.5f;
        for (int i = 1; i <= 64; i++, t += dt) {
            float ct = cosf(t), st = sinf(t);
            s = fmaxf(s, capsule(x, y, cx + r1 * ct, cy - r1 * st, cx + r2 * ct, cy - r2 * st, r) ? 1.0f : 0.0f);
        }
    }
    return s;
}


char *drawLineWithSampleBresenham() {
    // 底色初始为了黑色
    memset(img, 255, sizeof(img));
    unsigned char *p = img;
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++, p += 3) {
            p[0] = p[1] = p[2] = (unsigned char) ((1.0f - sample(x, y)) * 255);
        }
    }
    return img;
}
