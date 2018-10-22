//
// Created by Sophimp on 2018/10/21.
//

#ifndef CLIONOPENGL_LIGHT_H
#define CLIONOPENGL_LIGHT_H


class Light {

public:
    void sceneRender();
    void onProcessKeyEvent(unsigned char key);

    void onDisplayLoop(int elapseTime);

    void onMouseEvent(int button, int x, int y);
private:
};


#endif //CLIONOPENGL_LIGHT_H
