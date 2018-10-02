//
// Created by Sophimp on 2018/10/2.
//

#include <glad/glad.h>
#include "TextureRender.h"
#include "Shader.h"

static const GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f
};

static const GLfloat vertex_colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f,
};

static unsigned int indices[] = {
        0, 1, 3,
//        1, 2, 3
};

void TextureRender::render() {


    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_VERTEX_ARRAY, EBO);
    glBufferData(GL_VERTEX_ARRAY, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(2);

    // load and create a texture
    unsigned int texture;

    Shader ourShader("F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\basic_vertex.glsl",
                     "F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\basic_fragment.glsl");
    ourShader.use();

//    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);

    glBindAttribLocation(ourShader.programId, 0, "aPos");
    glBindAttribLocation(ourShader.programId, 1, "vertexColor");

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glBindVertexArray(VAO);

//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glFlush();
}
