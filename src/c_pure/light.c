
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