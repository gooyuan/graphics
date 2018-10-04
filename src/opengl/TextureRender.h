//
// Created by Sophimp on 2018/10/2.
//

#ifndef CLIONOPENGL_TEXTURERENDER_H
#define CLIONOPENGL_TEXTURERENDER_H


class TextureRender {

public:
    void render();

    void onMixValueChange(float mixValue);

private:
    void transformationRender(unsigned int shaderHandler);

};

#endif //CLIONOPENGL_TEXTURERENDER_H
