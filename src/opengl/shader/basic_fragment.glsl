#version 330 core

out vec4 FragColor;

// the input variable from the vertex shader (same name and same type)
in vec4 aColor;

void main(){
    FragColor = aColor;
}
