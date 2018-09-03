//
// Created by Sophimp on 2018/9/2.
//

#include <math.h>
#include <iostream>
#include <GL/gl.h>
#include "KochSnowFlake.h"

using namespace std;

KochSnowFlake::KochSnowFlake() {}

KochSnowFlake::~KochSnowFlake() {}

void KochSnowFlake::generateKochSnowFlake(Point p1, Point p2, Point p3, int depth) {
    len = static_cast<int>(3 + 3 * (pow(4, depth) - 1));
    kcPoints = new Point[len];

    cout << "length: " << len << '\n';

    // 原始的三个点
    kcPoints[index++] = p1;
    kcPoints[index++] = p2;
    kcPoints[index++] = p3;
    tmp[0] = p1;
    tmp[1] = p2;
    tmp[2] = p3;

    // 计算每条边的 koch curve
    generateKochCurve(p1, p2, depth);
    generateKochCurve(p2, p3, depth);
    generateKochCurve(p3, p1, depth);

    for (int i = 0; i < len; ++i) {
        cout << kcPoints[i].x << "," << kcPoints[i].y << '\n';
    }
}

/**
 * 生成曲线
 * 最终是要生成三角形, 所以, 递归产生的点是按三角形顶点顺序构成即可
 */
void KochSnowFlake::generateKochCurve(Point p1, Point p2, int depth) {
    if (depth == 1) {
//        tmp[0].x = (p1.x + p2.x) / 3.0;
//        tmp[0].y = (p1.y + p2.y) / 3.0;
//
//        tmp[2].x = (p1.x + p2.x) * 2 / 3.0;
//        tmp[2].y = (p1.y + p2.y) * 2 / 3.0;
//
//        tmp[1] = tmp[0] + (tmp[2] - tmp[0]).rotate(PI / 3);
        tmp[0].x = 2.0 / 3 * p1.x + 1.0 / 3 * p2.x;
        tmp[0].y = 2.0 / 3 * p1.y + 1.0 / 3 * p2.y;

        tmp[1].x = 1.0 / 3 * p1.x + 2.0 / 3 * p2.x;
        tmp[1].y = 1.0 / 3 * p1.y + 2.0 / 3 * p2.y;


        tmp[2] = tmp[0] + (tmp[1] - tmp[0]).rotate(PI / 3);
        kcPoints[index++] = tmp[0];
        kcPoints[index++] = tmp[1];
        kcPoints[index++] = tmp[2];
        cout << kcPoints[index].x << "," << kcPoints[index].y << '\n';
    } else {
//        generateKochCurve(p1, tmp[0], depth - 1);
//        generateKochCurve(tmp[0], tmp[1], depth - 1);
//        generateKochCurve(tmp[1], tmp[2], depth - 1);
//        generateKochCurve(tmp[2], p2, depth - 1);
    }
}

void KochSnowFlake::kochSnowRender() {
    generateKochSnowFlake(Point(-20.0, 20.0), Point(20.0, 20.0), Point(0, -20), 1);
    glColor3f(0.7, 0.5, 0.2);
    for (int i = 0; i < len; i+=3) {
        glBegin(GL_TRIANGLES);
        glVertex2f(kcPoints[i].x, kcPoints[i].y);
        glVertex2f(kcPoints[i+1].x, kcPoints[i+1].y);
        glVertex2f(kcPoints[i+2].x, kcPoints[i+2].y);
        glEnd();
    }

}


