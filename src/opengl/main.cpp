
// glad.h 放在第一行, 就不会与其他文件的#include冲突了
#include <glad/glad.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdio>
#include "PrimitiveRender.h"
#include "KochSnowFlake.h"
#include "TextureRender.h"

using namespace std;

void processKeyEvent(int key, int x, int y);

void ChangeSize(GLsizei w, GLsizei h) {
    // prevent divide by zero, when window is too short
    if (w < 1) w = 1;
    if (h < 1) h = 1;
    printf("%d %d\n", w, h);
    float ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // set the window to be the entire window
    glViewport(0,0,w,h);
//     if (w <= h)
//         glOrtho(-30.0, 30.0, -30.0 * (GLfloat) h / (GLfloat) w, 30.0 * (GLfloat) h / (GLfloat) w, -50.0, 50.0);
//     else
//         glOrtho(-30.0 * (GLfloat) w / (GLfloat) h, 30.0 * (GLfloat) w / (GLfloat) h, -30.0, 30.0, -50.0, 50.0);
//    gluPerspective(45, ratio, 1, 1000);
//    glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
}

static TextureRender *textureRenderPtr;
void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    // todo 渲染代码
    // 持续优化: 
    //  1. 当前渲染环境通用性 
    //  2. 渲染代码能否只调用一次, 根据实例来选择 
    //  3. 将所有的渲染代码都渲染出来呢

    // Primitive
//   PrimitiveRender *render = new PrimitiveRender();
//    render -> triangleRender();
//    render->quadRender();
//   delete render;

    // 科特雪花
    // KochSnowFlake *snowFlake = new KochSnowFlake();
    // snowFlake->kochSnowRender();
    // delete snowFlake;
    textureRenderPtr = new TextureRender();
    // texture
    textureRenderPtr->render();

    glutSwapBuffers();
}

static float mixValue = 0.0f;
void processKeyEvent(int key, int x, int y) {
    TextureRender::KeyEvent event = TextureRender::UP;
    switch (key){
        case GLUT_KEY_DOWN:
            mixValue -= 0.1f;
            mixValue = mixValue > 0.0f ? mixValue : 0.0f;
            event = TextureRender::DOWN;
            break;
        case GLUT_KEY_UP:
            event = TextureRender::UP;
            mixValue += 0.1f;
            mixValue = mixValue < 1.0f ? mixValue : 1.0f;
            break;
        case GLUT_KEY_LEFT:
            event = TextureRender::LEFT;
            break;
        case GLUT_KEY_RIGHT:
            event = TextureRender::RIGHT;
            break;

        default:break;
    }
    textureRenderPtr->onMixValueChange(event);
}

void timeDelayCallback(int elapseTime){

    textureRenderPtr->onDisplayLoop(glutGet(GLUT_ELAPSED_TIME));

//    glutPostRedisplay();

    glutTimerFunc(15, timeDelayCallback, 1);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);

//    float a = 2.0f;
//    float *p1 = &a;
//    double bb[5] ;
//    double *p2 = new double[5];
//    cout << sizeof(p2) << "-" << sizeof(bb) << "\n";

    glutCreateWindow("OpenGL Sophimp");

    // 初始化代码是有顺序的, 在这里可以正确初始化
    // 在glut初始化之后
    if(!gladLoadGL()) {
        std::cout << "Something went wrong!\n";
        exit(-1);
    }
    printf("OpenGL Version %d.%d loaded\n", GLVersion.major, GLVersion.minor);

    glClearColor(0.51, 0.51, 0.51, 0.5);

    // 光栅化到窗口的操作
     glutReshapeFunc(ChangeSize);

    // 这里是关键代码
    glutDisplayFunc(RenderScene);

    glutIdleFunc(RenderScene);

    // 键盘事件
    glutSpecialFunc(processKeyEvent);

    glutTimerFunc(15, timeDelayCallback, 1);

//    timeDelayCallback(glutGet(GLUT_ELAPSED_TIME));

    glutMainLoop();

    return 0;
}

