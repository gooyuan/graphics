
#include <GL/gl.h>
#include <stdio.h>
// 4 个顶点
static const GLfloat vertex_positions[] = {
    -1.0f, -1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 1.0f,
};

// 每个顶点颜色
static const GLfloat vertex_colors[] = {
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
};

// 三个索引值 
static const GLushort vertex_indices[] = {
    0, 1, 2
};

// 
void display(){
    // 设置元素数组缓存
    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

    // 设置顶点属性
    glGenVertextArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(vertex_positions) + sizeof(vertex_colors), 
        NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);

    // 绘制
    // draw arrays
    model_matrix = vmath::translation(-3.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // draw elements
    model_matrix = vmath::translation(-1.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSINGLED_SHORT, NULL);
    // draw element base vertex
    model_matrix = vmath::translation(1.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
    glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSINGLED_SHORT, NULL, 1);
    // draw arrays instanced
    model_matrix = vmath::translation(3.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);

    glutCreateWindow("OpenGL draw");

    glClearColor(0.51, 0.51, 0.51, 0.5);

    // 可以将函数当作参数传递, 不管是C,C++都是自有的么?
    glutReshapeFunc(ChangeSize);

    // 这里是关键代码
    glutDisplayFunc(display);

    glutMainLoop();

}