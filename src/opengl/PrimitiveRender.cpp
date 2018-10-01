#include <glad/glad.h>
#include "PrimitiveRender.h"
#include "Shader.h"

// 4 个顶点
static const GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f
};

// 每个顶点颜色
static const GLfloat vertex_colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f,
};

static float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f, 1.0f, // left
        -0.0f, -0.5f, 0.0f, 1.0f, // right
        -0.45f, 0.5f, 0.0f, 1.0f // top
};

static float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  1.0f, // left
        0.9f, -0.5f, 0.0f,  1.0f, // right
        0.45f, 0.5f, 0.0f,  1.0f // top
};
// 三个索引值
static const GLushort vertex_indices[] = {0, 1, 2};

void PrimitiveRender::triangleRender() {
    GLuint VAOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // bind, bufferData, pointer 顺序执行, enable可以在不管顺序
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

//    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);

    // 释放绑定
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

//    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);

    // 着色器
//    Shader basicShader("shader/basic_vertex.glsl", "shader/basic_fragment.glsl");
    Shader basicShader("F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\basic_vertex.glsl",
                       "F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\basic_fragment.glsl");
    basicShader.use();

//    int vertexColorLocation = glGetUniformLocation(basicShader.programId, "vertexColor");
//    std::cout << vertexColorLocation << std::endl;

    // 确保在 shader 编译之后
    glBindAttribLocation(basicShader.programId, 0, "aPos");
    glBindAttribLocation(basicShader.programId, 1, "vertexColor");

    // 线框模式
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glBindVertexArray(VAOs[0]);
    glBindBuffer(0, VBOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

//    glBindVertexArray(VAOs[1]);
//    glDrawArrays(GL_TRIANGLES, 0, 3);

//    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glFlush();
}

void PrimitiveRender::quadRender() {
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

PrimitiveRender::PrimitiveRender() {}

PrimitiveRender::~PrimitiveRender() {}
