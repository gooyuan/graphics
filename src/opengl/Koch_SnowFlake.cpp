//
// Created by Sophimp on 2018/9/2.
//

#include <math.h>
#include "Koch_SnowFlake.h"

Koch_SnowFlake::Koch_SnowFlake() {}

Koch_SnowFlake::~Koch_SnowFlake() {}

Point *Koch_SnowFlake::generateKochSnowFlake(Point p1, Point p2, Point p3, int depth) {
    depth = 5;
    int len = static_cast<int>(3 + 3 * (pow(4, depth) - 1));
    kcPoints = new Point[len];

    // 原始的三个点
    kcPoints[index++] = p1;
    kcPoints[index++] = p2;
    kcPoints[index++] = p3;

    // 计算每条边的 koch curve
    for (int i=0; i<depth; i++){
//        generateKochCurve()
    }

    return kcPoints;
}

/**
 * 生成曲线
 */
Point* Koch_SnowFlake::generateKochCurve(Point* p, int depth) {

}

Point *Koch_SnowFlake::createSidePoints(Point p1, Point p2) {
    Point* tmp = new Point[4];
    tmp[1] = p1;
    tmp[2] = p2;
    return nullptr;
}


