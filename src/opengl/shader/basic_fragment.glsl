#version 330 core

out vec4 FragColor;

// the input variable from the vertex shader (same name and same type)
in vec3 aColor;
in vec2 TexCood;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixAlpha;

void main(){
//    FragColor = aColor;
    FragColor = texture(texture1, TexCood) * vec4(aColor, 1.0f);
    FragColor = mix(texture(texture1, TexCood) * vec4(aColor, 1.0f), texture(texture2, TexCood), mixAlpha);
}

