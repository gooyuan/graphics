//
// Created by Sophimp on 2018/9/2.
//

#ifndef CLIONOPENGL_KOCH_SNOWFLAKE_H
#define CLIONOPENGL_KOCH_SNOWFLAKE_H


#include "Point.h"

/**
 * 思路:
 *  1. 给出三个顶点, 画一三角形
 *  2. 循环(层数与等分迭代次数一致), 迭代, 等分每条边
 *  3. 求出所有的点后, 使用OpenGL将这些点画出来
 *
 */
class KochSnowFlake{
public:
    KochSnowFlake();
    ~KochSnowFlake();

    /**
     * 生成科特雪花所有点
     */
    void generateKochSnowFlake(Point p1, Point p2, Point p3, int depth);

    void kochSnowRender();

private:

    int depth;

    /**
     * 存放所有的点
     */
    Point *kcPoints;

    /**
     * 生成每条边的点
     */

    void generateKochCurve(Point p1, Point p2, int depth);

    int index;

    /**
     * 每条边临时生成数据
     */
    Point tmp[3];

    const double PI = 3.1415926;
    int len;
};


#endif //CLIONOPENGL_KOCH_SNOWFLAKE_H
