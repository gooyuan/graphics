#version 330 core

// the position variable has attribute position 0
layout (location=0) in vec3 aPos;

// specify a color output to a fragment shader
out vec4 vertexColor;

void main(){
    // gl_Position 全局变量?
    // see how we directly give a vec3 to vec4's constructor
    gl_Position = vec4(aPos, 1.0);
    // see the output variable to a dark-red color
    vertexColor = vec4(0.5, 0.5, 0.0, 1.0);
}