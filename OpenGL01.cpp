
#include <GL/glut.h>
#include <stdio.h>

void render_1(int i, char *pString[]);

void render_2(int argc, char **argv);


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

void DrawMyObjects() {
    //画四边形
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.5, 0.2);
    glVertex2f(-7, -3);
    glVertex2f(-5.5, -1);
    glVertex2f(-1, -0.5);
    glVertex2f(-1, -4);
    glColor3f(0.5, 0.7, 0.2);
    glVertex2f(2, -6.25);
    glVertex2f(2.5, -1);
    glVertex2f(6.5, 1);
    glVertex2f(4.5, -6.25);

    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(-0.5f, -0.5f);    // x, y
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);

    glEnd();
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    // Draw a Red 1x1 Square centered at origin
    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(-0.5f, -0.5f);    // x, y
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    glFlush();  // Render now
}

void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);
    DrawMyObjects();
//    display();
    glFlush();
}


int main(int argc, char **argv) {
    render_1(argc, argv);
    return 0;
}

void render_1(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);

    glutCreateWindow("OpenGL Sophimp");

    glClearColor(0.51, 0.51, 0.51, 0.5);

    // 可以将函数当作参数传递, 不管是C,C++都是自有的么?
    glutReshapeFunc(ChangeSize);

    // 这里是关键代码
    glutDisplayFunc(RenderScene);


    glutMainLoop();

}