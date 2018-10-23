//
// Created by Sophimp on 2018/10/21.
//
#include "Light.h"
#include <glad/glad.h>
#include <stdio.h>
#include "Shader.h"
#include "Camera.h"

static const bool isCompany = true;
static float changeValue = 0.0f;

static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

static float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

static glm::vec3 lightPos(-3.2f, -3.0f, -8.0f);

static unsigned int VBO = 0, cubeVAO, lightVAO;
static Shader *lightingShader, *lampShader;
static Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

void init() {
    glGenVertexArrays(1, &cubeVAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 一个vertex array 需要配对vertex buffer, 实际数据与buffer绑定, 操作使用vertex来取
    // 这就好像buffer是堆内存, vertex 只是pointer
    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    // we only need to bind the VBO(to link it with glVertexAttribPointer), no need to fill it
    // the VBO's data already contains all we need(it's already bound, but we do it again for educational purpose)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    if (isCompany) {
        lightingShader = new Shader("shader/color_vertex.glsl", "shader/color_fragment.glsl");
        lampShader = new Shader("shader/lamp_vertex.glsl", "shader/lamp_fragment.glsl");
    } else {
        lightingShader = new Shader("F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\color_vertex.glsl",
                                    "F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\color_fragment.glsl");
        lampShader = new Shader("F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\lamp_vertex.glsl",
                                "F:\\code\\opengl\\CLionOpenGL\\src\\opengl\\shader\\lamp_fragment.glsl");
    }

}

void Light::sceneRender() {
    if (VBO == 0) {
        init();
    }

    // do render
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    lightingShader->use();
    lightingShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    lightingShader->setVec3("lightPos", lightPos);

    //view/projection  transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1.0f, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    lightingShader->setMat4("projection", projection);
    lightingShader->setMat4("view", view);

    // world transformation
    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(-120.0f), glm::vec3(1.0f, 0.3f, 0.5f));
    lightingShader->setMat4("model", model);

    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // also draw the lamp object
    lampShader->use();
    lampShader->setMat4("projection", projection);
    lampShader->setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    // model = glm::rotate(model, glm::radians(20.0f * changeValue), glm::vec3(1.0f, 0.3f, 0.5f));
//    model = glm::scale(model, glm::vec3(0.2f));
    lampShader->setMat4("model", model);

    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}


void Light::onProcessKeyEvent(unsigned char key) {
    changeValue += deltaTime;
    switch (key) {
        case 'w':
            camera.ProcessKeyBoard(CAMERA_DIRECTION::FORWARD, deltaTime);
            break;
        case 's':
            camera.ProcessKeyBoard(CAMERA_DIRECTION::BACKWARD, deltaTime);
            break;
        case 'a':
            camera.ProcessKeyBoard(CAMERA_DIRECTION::LEFT, deltaTime);
            break;
        case 'd':
            camera.ProcessKeyBoard(CAMERA_DIRECTION::RIGHT, deltaTime);
            break;
    }
}

void Light::onDisplayLoop(int elapseTime) {
    deltaTime = (elapseTime - lastFrame) / 300.0f;
    lastFrame = elapseTime;
    changeValue += deltaTime;
//    printf("delta time: %f \n ", deltaTime);
    sceneRender();
}

static float lastX = 600 / 2.0f;
static float lastY = 600 / 2.0f;
static bool firstMouse = true;

void Light::onMouseEvent(int button, int x, int y) {
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

