#version 330 core

// the position variable has attribute position 0
//in vec4 aPos;
//in vec4 vertexColor;
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 vertexColor;
layout (location=2) in vec2 aTexCood;
// specify a color output to a fragment shader
out vec3 aColor;
out vec2 TexCood;

uniform mat4 transform;
void main(){
    // gl_Position 全局变量?
    gl_Position = transform * vec4(aPos, 1.0f);
//    gl_Position = vec4(aPos, 1.0f);
    // see the output variable to a dark-red color
//    aColor = vec4(0.5, 0.5, 0.5, 1.0);
    aColor = vertexColor;
    TexCood = aTexCood;
}