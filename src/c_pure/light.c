
#include "light.h"
#include "pub.h"

#define W 512
#define H 512

static char img[W * H * 3];

/**
 * 圆的符号距离场
 * @param ox, oy 任意一点
 * @param cx, cy 圆心
 * @param r 圆半径
 */
float circleSDF(float ox, float oy, float cx, float cy, float r){
    float ux = cx - ox, uy = cy - oy;
    return sqrtf(ux * ux + uy * uy) -r;
}

/**
 * 光线步进追踪
 */
#define MAX_STEP 10
// 描述光是按直线上的单位的长度, 这里与半径一致, 就可以步进到 
#define MAX_DISTANCE 2.0f
// 这是一个什么常量呢? sdf 与之比较, 那就是指边接近边界的值
#define EPSILON 1e-6f

/**
 * ray tracing, 求出光线与场景的最近点
 * ray marching,又称 sphere tracing
 * 光的强弱: 离光源越近, 光越强, 反之, 越弱
 * 因此, 光的采样结果, 需保证, 由内向外, 越来越弱, 分层采样比较容易看出
 * 
 */
float trace(float ox, float oy, float cosx, float sinx){
    // 斜边上步进距离, 这个距离跟圆心的单位距离不一样, 步进跟次数相关
    float t = 0.0f;
    for(int i=0; i < MAX_STEP && t < MAX_DISTANCE; i++){
        // ox, oy 来来是光栅格点的坐标
        float sd = circleSDF(ox + cosx * t, oy + sinx * t, 0.5f, 0.5f, 0.1f);
        if (sd < EPSILON){
            // 结果是用来统计的, 只有2.0 与 0.0两种情况
            // 可控制当前颜色深度, 2.0 说明当前点
            return 5.0f;
        }
        t += sd;
    }
    // 光照射不到的范围
    return 0.0f;
}

/**
 * 蒙特卡罗积分
 * 随机采样N个方向, 然后计算平均值
 */
#define TWO_PI 6.28318530718f
#define N 64
/**
 * 每一点光强(比例)
 */
static float sample(float x, float y){
    float sum = 0.0f;
    for(int i=0; i<N; i++){
        // 用来生成一个随机角度
        // float a = TWO_PI * rand() / RAND_MAX;        // 均匀采样
        float a = TWO_PI * i / N;                    // 分层采样
        // float a = TWO_PI * (i + (float)rand() / RAND_MAX) / N;                    // 抖动采样
        // 算出来
        // sum += trace(x, y, cosf(a), sinf(a));
        sum += trace(x, y, cosf(a), sinf(a));
    }
    return sum / N;
}

unsigned char* drawBasicLight(){
    char* p = img;
    // 这里怎么不需要memset?
    for(int y=0; y<H; y++){
        for (int x=0; x<W; x++, p+=3){
            // 这里为何要 这里是将坐标单位化, 圆心是按0.5, 0.5来算的
            // p[0] = p[1] = p[2] = (int)fminf(sample((float)x/W, (float)y/H)*255.0f, 255.0f);
            p[0] = (int)fminf(sample((float)x/W, (float)y/H)*255.0f, 255.0f);
            p[1] = (int)fminf(sample((float)x/W, (float)y/H)*255.0f, 255.0f);
            p[2] = 0;
        }
    }
    return img;
}

typedef struct {float sdf, emissive;} Result;

/**
 * 并集
 */
Result unionOp(Result a, Result b){
    return a.sdf < b.sdf ? a : b;
}

/**
 * 交集
 */
Result intersectOp(Result a, Result b){
    Result r = a.sdf < b.sdf ? a : b;
    r.sdf = a.sdf < b.sdf ? b.sdf : a.sdf;
    return r;
}

/**
 * 另一个相交的补集
 */
Result subtractOp(Result a, Result b){
    Result r = a;
    r.sdf = (a.sdf > -b.sdf) ? a.sdf : -b.sdf;
    return r;
}

static Result scene(float x, float y){
    Result r1 = {circleSDF(x, y, 0.4f, 0.5f, 0.2f), 1.0f};
    Result r2 = {circleSDF(x, y, 0.6f, 0.5f, 0.2f), 0.8f};
    // return unionOp(r1, r2);
    return intersectOp(r1, r2);
    // return subtractOp(r1, r2);
    // return subtractOp(r2, r1);
} 

float trace_s(float ox, float oy, float cosx, float sinx){
    float t = 0.0f;
    for(int i=0; i<MAX_STEP && t < MAX_DISTANCE; i++){
        Result r = scene(ox + t*cosx, oy + t*sinx);
        if(r.sdf < EPSILON){
            return r.emissive; 
        }
        t += r.sdf;
    }
    return 0.0f;
}

float sample_s(float x, float y){
    float sum = 0.0f;
    for(int i=0; i<N; i++){
        // float a = i* TWO_PI / N;
        float a = (i + (float)rand() / RAND_MAX) * TWO_PI / N;
        sum += trace_s(x, y, cosf(a), sinf(a));
    }
    return sum / N;
}

unsigned char* drawCSGLight(){
    char* p = img;
    // 这里怎么不需要memset?
    for(int y=0; y<H; y++){
        for (int x=0; x<W; x++, p+=3){
            // 这里为何要 这里是将坐标单位化, 圆心是按0.5, 0.5来算的
            p[0] = p[1] = p[2] = (int)fminf(sample_s((float)x/W, (float)y/H)*255.0f, 255.0f);
        //     p[0] = (int)fminf(sample((float)x/W, (float)y/H)*255.0f, 255.0f);
        //     p[1] = (int)fminf(sample((float)x/W, (float)y/H)*255.0f, 255.0f);
        //     p[2] = 0;
        }
    }
    return img;
}

float segmentSDF(float x, float y, float ax, float ay, float bx, float by){
    float vx = x - ax, vy = y - ay, ux = bx - ax, uy = by - ay;
    float t = fmaxf(fminf((vx * ux + vy * uy)/(ux * ux + uy * uy), 1.0f), 0.0f);
    float dx = vx - ux * t, dy = vy - uy * t;
    return sqrtf(dx *dx + dy * dy);
}

float capsuleSDF_2(float x, float y, float ax, float ay, float bx, float by, float r){
    return segmentSDF(x, y, ax, ay, bx, by) - r;
}

float planeSDF(float x, float y, float px, float py, float nx, float ny){
    return (x - px) * nx + (y - py) * ny;
}

float rectangleSDF(float x, float y, float cx, float cy, float theta, float sx, float sy){
    // 关于 cx,cy 中心对称, 所以可以旋转到第一期限来做
    float cosTheta = cosf(theta), sinTheta = sinf(theta);
    float dx = fabs((x - cx) * cosTheta + (y - cx) * sinTheta) - sx;
    float dy = fabs((y - cy) * cosTheta - (x - cx) * sinTheta) - sy;
    float ax = fmaxf(dx,0.0f), ay = fmaxf(dy, 0.0f);
    return fminf(fmaxf(ax, ay), 0.0f) + sqrtf(ax * ax + ay * ay);
}

/**
 * 直接来三个顶点
 */
float triangleSDF(float x, float y, float ax, float ay, float bx, float by, float cx, float cy){
    // 求出点到三条边的最小距离
    float d = fminf(fminf(segmentSDF(x, y, ax, ay, bx, by), segmentSDF(x, y, ax, ay, cx, cy)), segmentSDF(x, y, bx, by, cx, cy));
    return (bx - ax) * (y - ay) > (by - ay) * (x - ax) &&
            (cx - bx) * (y - by) > (cy - by) * (x - bx) &&
            (ax - cx) * (y - cy) > (ay - cy) * (x - cx) ? -d : d;
}

static Result shapeScene(float x, float y){
    Result r1 = {rectangleSDF(x, y, 0.3f, 0.3f, TWO_PI / 12, 0.3f, 0.2f), 1.0f};
    Result r2 = {capsuleSDF_2(x, y, 0.5f, 0.6f, 0.6f, 0.5f, 0.1f), 1.5f};
    Result r3 = {triangleSDF(x, y, 0.7f, 0.5f, 0.4f, 0.6f, 0.6f, 0.6f), 0.8f};
    return unionOp(unionOp(r1, r2), r3);
}
float traceShape(float ox, float oy, float cosx, float sinx){
    float t = 0.0f;
    for(int i=0; i<MAX_STEP && t < MAX_DISTANCE; i++){
        Result r = shapeScene(ox + t*cosx, oy + t*sinx);
        if(r.sdf < EPSILON){
            return r.emissive; 
        }
        t += r.sdf;
    }
    return 0.0f;
}

float sampleShape(float x, float y){
    float sum = 0.0f;
    for(int i=0; i<N; i++){
        // float a = i* TWO_PI / N;
        float a = (i + (float)rand() / RAND_MAX) * TWO_PI / N;
        sum += traceShape(x, y, cosf(a), sinf(a));
    }
    return sum / N;
}

unsigned char* drawShapes(){
    char* p = img;
    // 这里怎么不需要memset?
    for(int y=0; y<H; y++){
        for (int x=0; x<W; x++, p+=3){
            // 这里为何要 这里是将坐标单位化, 圆心是按0.5, 0.5来算的
            p[0] = p[1] = p[2] = (int)fminf(sampleShape((float)x/W, (float)y/H)*255.0f, 255.0f);
        //     p[0] = (int)fminf(sample((float)x/W, (float)y/H)*255.0f, 255.0f);
        //     p[1] = (int)fminf(sample((float)x/W, (float)y/H)*255.0f, 255.0f);
        //     p[2] = 0;
        }
    }
    return img;

}