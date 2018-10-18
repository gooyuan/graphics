//
// Created by Sophimp on 2018/10/2.
//

#include "TextureRender.h"
#include "Shader.h"
#include <iostream>
#include <gtc/type_ptr.inl>
#include "stb_image.h"
#include "Camera.h"

// 公司与私人环境切换
#define isCompany 1

float vertices_cube[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};
static const GLfloat vertices[] = {
        // vertex               colors              // texture coordinate
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // left-bottom
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f,  // left-top
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 2.0f,  // right-top
        0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 2.0f, 0.0f   // right-bottom
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

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};
static float mixValue = 0.3f;


// timing
int *pInt;
static int deltaTime = 0;    // time between current frame and last frame
static int lastFrame = 0;
static int lastX = 300, lastY = 300;

unsigned int VAO = 0, VBO, EBO;
unsigned int texture[2];

static Shader *shaderPtr;

void doRender(Shader *shader);

void transformationRender(unsigned int shaderHandler, int index);

static Camera camera(glm::vec3(0.0f, 0.0f, 0.3f));

void TextureRender::render() {
    if (VAO == 0) {
        init();
    }
    doRender(shaderPtr);
}

void TextureRender::onMixValueChange(KeyEvent event) {
    mixValue += 0.01f;
    switch (event) {
        case UP:
            camera.ProcessKeyBoard(FORWARD, deltaTime / 500.0f);
            break;
        case DOWN:
            camera.ProcessKeyBoard(BACKWARD, deltaTime / 500.0f);
            break;
        case LEFT:
            camera.ProcessKeyBoard(CAMERA_DIRECTION::LEFT, deltaTime / 500.0f);
            break;
        case RIGHT:
            camera.ProcessKeyBoard(CAMERA_DIRECTION::RIGHT, deltaTime / 500.0f);
            break;
    }
    // printf("deltaTime: %d\n", deltaTime);
//     printf("cameraPos: (%f,%f,%f)\n", camera.Position.x, camera.Position.y, camera.Position.z);
//    if (mixValue > 1.0f){
//        mixValue = 0.1f;
//    }
//    render();
}

bool firstMouse = true;

void TextureRender::onMouseMove(int button, int x, int y) {
//    printf("%d-(%d,%d)\n", button, x, y);
    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }
    float xoffset = x - lastX;
    float yoffset = y - lastY;
    lastX = x;
    lastY = y;

    camera.ProcessMouseMovement(true, xoffset, yoffset);

    // mouse wheel
    if (button == 3) {
        camera.ProcessMouseScroll(1);
    } else if (button == 4) {
        camera.ProcessMouseScroll(-1);
    }
}

void TextureRender::onDisplayLoop(int elapseTime) {
    mixValue += 0.01f;
//    printf("elapseTime: %d\n", elapseTime);
    deltaTime = elapseTime - lastFrame;
    lastFrame = elapseTime;
//    printf("deltaTime: %d\n", deltaTime);
    render();
}

void TextureRender::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // 使用两个buffer 如何搞, 还是说, OpenGL默认就要这样处理一个buffer 带多个信息
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);

//    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // load and create a texture
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
    unsigned char *data;
    if (isCompany) {
        data = stbi_load("images/Flare_1.jpg", &width, &height, &nrChannels, 0);
    } else {
        data = stbi_load("F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\images\\Flare_1.jpg", &width, &height,
                         &nrChannels, 0);
    }
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
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
    unsigned char *data2;
    if (isCompany) {
        data2 = stbi_load("images/awesomeface.png", &width, &height, &nrChannels, 0);
    } else {
        data2 = stbi_load("F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\images\\awesomeface.png", &width,
                          &height, &nrChannels, 0);
    }
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "failed to load texture" << std::endl;
    }
    stbi_image_free(data2);

    if (isCompany) {
        shaderPtr = new Shader("shader/basic_vertex.glsl", "shader/basic_fragment.glsl");
    } else {
        shaderPtr = new Shader("F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\basic_vertex.glsl",
                               "F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\basic_fragment.glsl");
    }

    shaderPtr->use();
    glUniform1i(glGetUniformLocation(shaderPtr->programId, "texture1"), 0);
    shaderPtr->setInt("texture2", 1);
    shaderPtr->setFloat("mixAlpha", mixValue);

}

void doRender(Shader *shader) {

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    glm::mat4 view = camera.GetViewMatrix();
    shaderPtr->setMat4("view", view);

    glBindVertexArray(VAO);

    for (int i = 0; i < 10; ++i) {
        transformationRender(shader->programId, i);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
//    transformationRender(ourShader.programId);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//    glDrawArrays(GL_TRIANGLES, 0, 36);

//    glFlush();

}

void transformationRender(unsigned int shaderHandler, int index) {
    glm::mat4 transform(1.0f);
    float angle = 20 * (index + 1) * mixValue;
//    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
//    transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));

    // 3D
    glm::mat4 model(1.0f), view(1.0f), projection(1.0f);
//    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    float radius = 10.0f;
    float camX = sin(mixValue) * radius;
    float camZ = cos(mixValue) * radius;
//    view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.1f, 0.0f));
//    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(camera.Zoom), 1.0f, 0.1f, 100.0f);

//    unsigned int transformLoc = glGetUniformLocation(shaderHandler, "transform");
//    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

//    model = glm::rotate(model, angle * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    model = glm::translate(model, cubePositions[index]);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

    unsigned int modelLoc = glGetUniformLocation(shaderHandler, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

//    unsigned int viewLoc = glGetUniformLocation(shaderHandler, "view");
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

    unsigned int projectLoc = glGetUniformLocation(shaderHandler, "projection");
    glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));

//    transform = glm::rotate(transform, )
    //

}


