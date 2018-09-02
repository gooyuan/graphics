
#ifndef PRIMITIVERENDER_H
#define PRIMITIVERENDER_H

// #include "IRender.h"

/**
 * point, line, triangle, quad draw
 * 
 */
class PrimitiveRender {

    //
public:
    PrimitiveRender();

    void triangleRender();

    void quadRender();

    void vertexRender();

    ~PrimitiveRender();

private:

};

#endif