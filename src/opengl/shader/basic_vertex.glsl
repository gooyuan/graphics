#version 330 core

// the position variable has attribute position 0
in vec4 aPos;
in vec4 vertexColor;
//layout (location=0) in vec4 aPos;
//layout (location=1) in vec4 vertexColor;
// specify a color output to a fragment shader
out vec4 aColor;

void main(){
    // gl_Position 全局变量?
    // see how we directly give a vec3 to vec4's constructor
    gl_Position = vec4(aPos.x, -aPos.y, aPos.z, aPos.w);
    // see the output variable to a dark-red color
//    vertexColor = vec4(0.5, 0.5, 0.5, 1.0);
    aColor = vertexColor;
}