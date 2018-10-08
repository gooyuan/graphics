//
// Created by Sophimp on 2018/10/2.
//

#include <glad/glad.h>
#include "TextureRender.h"
#include "Shader.h"
#include <iostream>
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

static const GLfloat vertices[] = {
        // vertex               colors              // texture coordinate
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // left-bottom
        -0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 1.0f,   0.0f, 2.0f,  // left-top
        0.5f, 0.5f, 0.0f,       0.0f, 1.0f, 0.0f,   2.0f, 2.0f,  // right-top
        0.5f, -0.5f, 0.0f,      0.5f, 0.5f, 0.5f,   2.0f, 0.0f   // right-bottom
};

static const GLfloat vertex_colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f
};

static unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
};

static float mixValue = 0.3f;
void TextureRender::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // 使用两个buffer 如何搞, 还是说, OpenGL默认就要这样处理一个buffer 带多个信息
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // load and create a texture
    unsigned int texture[2];
    glGenTextures(2, texture);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    // set texture wrapping parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // set texture filtering parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    // unsigned char* data = stbi_load("F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\images\\Flare_1.jpg", &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load("images/Flare_1.jpg", &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else{
        std::cout << "failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    // set texture wrapping parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // set texture filtering parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char* data2 = stbi_load("images/awesomeface.png", &width, &height, &nrChannels, 0);
    if(data2){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else{
        std::cout << "failed to load texture" << std::endl;
    }
    stbi_image_free(data2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    Shader ourShader("shader/basic_vertex.glsl", "shader/basic_fragment.glsl");
    // Shader ourShader("F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\basic_vertex.glsl",
                    //  "F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\basic_fragment.glsl");
//    shaderPtr = new Shader("F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\basic_vertex.glsl",
//                     "F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shaderPtr\\basic_fragment.glsl");
    ourShader.use();

    glUniform1i(glGetUniformLocation(ourShader.programId, "texture1"), 0);
    ourShader.setInt("texture2", 1);
    ourShader.setFloat("mixAlpha", mixValue);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    transformationRender(ourShader.programId);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//    glDrawArrays(GL_TRIANGLES, 0, 3);

//    glFlush();
}

void TextureRender::onMixValueChange(float value) {
    std::cout << "mixValue: " << value << std::endl;
    mixValue += 0.001f;
    if (mixValue > 1.0f){
        mixValue = 0.1f;
    }
    render();
}

void TextureRender::transformationRender(unsigned int shaderHandler) {
    glm::mat4 transform(1.0f);
    float angle = mixValue * 2 * PI;
//    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));

    unsigned int transformLoc = glGetUniformLocation(shaderHandler, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
//    transform = glm::rotate(transform, )
    //

}
