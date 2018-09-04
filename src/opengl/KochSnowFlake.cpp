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

void KochSnowFlake::generateKochSnowFlake(Point a1, Point a2, Point a3, int depth)
{
    len = static_cast<int>(3 + 3 * (pow(4, depth) - 1));
    kcPoints = new Point[len];

    // cout << "length: " << len << '\n';

    // 原始的三个点
    kcPoints[index++] = a1;
    kcPoints[index++] = a2;
    kcPoints[index++] = a3;

    // 计算每条边的 koch curve
    generateKochCurve(a1, a2, depth);
    generateKochCurve(a2, a3, depth);
    generateKochCurve(a3, a1, depth);

    // for (int i = 0; i < len; ++i)
    // {
    //     cout << kcPoints[i].x << "," << kcPoints[i].y << '\n';
    // }
}

/**
 * 生成科特曲线:
 * 1. 每两点之间生成三个点, 按首尾点顺序缓存
 * 2. 首尾点再结合上一步生成的三点, 继续生成每两点的科特曲线, 除数递减, 直至为0返回 
 * 3. 使用 openGL画三角, 是按每三个点一组来画, 所以在递归运算每一步生成的三个点, 可以直存入缓存区
 */
void KochSnowFlake::generateKochCurve(Point p1, Point p2, int depth)
{
    if (depth == 0)
    {
        return;
    }

    Point tmp[3];

    tmp[0].x = 2.0 / 3 * p1.x + 1.0 / 3 * p2.x;
    tmp[0].y = 2.0 / 3 * p1.y + 1.0 / 3 * p2.y;

    // 按首尾顺序缓存, 旋转得到的点放中间
    tmp[2].x = 1.0 / 3 * p1.x + 2.0 / 3 * p2.x;
    tmp[2].y = 1.0 / 3 * p1.y + 2.0 / 3 * p2.y;

    // Point b = tmp[1] - tmp[0];
    // cout << "side: "<< b.x << "," << b.y <<'\n';
    // b = b.rotate(PI/3);
    // cout << "side: " << b.x << "," << b.y <<'\n';
    tmp[1] = tmp[0] + (tmp[2] - tmp[0]).rotate(PI / 3);
    kcPoints[index++] = tmp[0];
    kcPoints[index++] = tmp[1];
    kcPoints[index++] = tmp[2];
    // cout << kcPoints[index].x << "," << kcPoints[index].y << '\n';
    generateKochCurve(p1, tmp[0], depth - 1);
    generateKochCurve(tmp[0], tmp[1], depth - 1);
    generateKochCurve(tmp[1], tmp[2], depth - 1);
    generateKochCurve(tmp[2], p2, depth - 1);
}

void KochSnowFlake::kochSnowRender()
{
    // todo OpenGL 的坐标不是单位坐标吗? 为何划定了一个600*600, 这里使用 -10, 就能占据 1/3 个窗口
    generateKochSnowFlake(Point(-10.0, 10.0), Point(10.0, 10.0), Point(0, -10), 5);
    glColor3f(0.7, 0.5, 0.2);
    // 只是简单的画三角形, 每个顶点处理一下, 会有什么样的效果?
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < len; i++)
    {
        glVertex2f(kcPoints[i].x, kcPoints[i].y);
    }
    glEnd();

    delete kcPoints;
}
