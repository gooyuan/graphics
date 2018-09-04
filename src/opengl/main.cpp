
#include <GL/glut.h>
#include <iostream>
#include <cstdio>
#include "PrimitiveRender.h"
#include "KochSnowFlake.h"

using namespace std;

void ChangeSize(GLsizei w, GLsizei h) {
    if (w < 1) w = 1;
    if (h < 1) h = 1;
    printf("%d %d\n", w, h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-30.0, 30.0, -30.0 * (GLfloat) h / (GLfloat) w, 30.0 * (GLfloat) h / (GLfloat) w, -50.0, 50.0);
    else
        glOrtho(-30.0 * (GLfloat) w / (GLfloat) h, 30.0 * (GLfloat) w / (GLfloat) h, -30.0, 30.0, -50.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);

    // todo 渲染代码
    // 持续优化: 
    //  1. 当前渲染环境通用性 
    //  2. 渲染代码能否只调用一次, 根据实例来选择 
    //  3. 将所有的渲染代码都渲染出来呢

    // Primitive
//    PrimitiveRender *render = new PrimitiveRender();
    // render.triangleRender();
//    render->quadRender();
//    delete render;

    // 科特雪花
    KochSnowFlake *snowFlake = new KochSnowFlake();
    snowFlake->kochSnowRender();
    delete snowFlake;
    
    glFlush();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);

//    float a = 2.0f;
//    float *p1 = &a;
//    double bb[5] ;
//    double *p2 = new double[5];
//    cout << sizeof(p2) << "-" << sizeof(bb) << "\n";

    glutCreateWindow("OpenGL Sophimp");

    glClearColor(0.51, 0.51, 0.51, 0.5);

    // 可以将函数当作参数传递, 不管是C,C++都是自有的么?
    glutReshapeFunc(ChangeSize);

    // 这里是关键代码
    glutDisplayFunc(RenderScene);

    glutMainLoop();

    return 0;
}

