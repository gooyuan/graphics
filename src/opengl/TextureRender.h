//
// Created by Sophimp on 2018/10/2.
//

#ifndef CLIONOPENGL_TEXTURERENDER_H
#define CLIONOPENGL_TEXTURERENDER_H


class TextureRender {

public:
    enum KeyEvent{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    void render();

    void onMixValueChange(KeyEvent event);

    void onDisplayLoop(int elapseTime);

    void onMouseMove(int button, int x, int y);

private:
    void transformationRender(unsigned int shaderHandler, int index);

    const float PI = 3.141592653f;

    void init();
};

#endif //CLIONOPENGL_TEXTURERENDER_H
