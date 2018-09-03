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
    Point* generateKochSnowFlake(Point p1, Point p2, Point p3, int depth);

private:

    int depth;

    /**
     * 存放所有的点
     */
    Point *kcPoints;

    /**
     * 生成每条边的点
     */

    Point* generateKochCurve(Point* p, int depth);

    Point* createSidePoints(Point p1, Point p2);
    int index;
};


#endif //CLIONOPENGL_KOCH_SNOWFLAKE_H
