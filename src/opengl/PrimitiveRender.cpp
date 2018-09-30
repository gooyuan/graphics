#include <glad/glad.h>
#include "PrimitiveRender.h"
#include "Shader.h"

// 4 个顶点
static const GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 1.0f,
//        0.5f, 0.5f, 0.0f, 1.0f
};

// 每个顶点颜色
static const GLfloat vertex_colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
//        0.5f, 0.5f, 0.5f, 1.0f,
};

// 三个索引值
static const GLushort vertex_indices[] = {0, 1, 2};

void PrimitiveRender::triangleRender() {
    GLuint VAO, VBO, VCO;
//    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VAO);
//    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VCO);

    // bind, bufferData, pointer 顺序执行, enable可以在不管顺序
    glBindBuffer(GL_ARRAY_BUFFER, VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VCO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
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

//    glBindVertexArray(VAO);
    glBindAttribLocation(basicShader.programId, 0, "aPos");
    glBindAttribLocation(basicShader.programId, 1, "vertexColor");


    glDrawArrays(GL_TRIANGLES, 0, 4);

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
// void PrimitiveRender::vertexRender(){
//     // 设置元素数组缓存
//     glGenBuffers(1, ebo);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

//     // 设置顶点属性
//     glGenVertextArrays(1, vao);
//     glBindVertexArray(vao[0]);
//     glGenBuffers(1, vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
//     glBufferData(GL_ARRAY_BUFFER,
//         sizeof(vertex_positions) + sizeof(vertex_colors), 
//         NULL, GL_STATIC_DRAW);
//     glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
//     glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);

//     // 绘制
//     // draw arrays
//     model_matrix = vmath::translation(-3.0f, 0.0f, -5.0f);
//     glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
//     glDrawArrays(GL_TRIANGLES, 0, 3);
//     // draw elements
//     model_matrix = vmath::translation(-1.0f, 0.0f, -5.0f);
//     glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
//     glDrawElements(GL_TRIANGLES, 3, GL_UNSINGLED_SHORT, NULL);
//     // draw element base vertex
//     model_matrix = vmath::translation(1.0f, 0.0f, -5.0f);
//     glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
//     glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSINGLED_SHORT, NULL, 1);
//     // draw arrays instanced
//     model_matrix = vmath::translation(3.0f, 0.0f, -5.0f);
//     glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
//     glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);

// }
