#version 330 core
in vec4 vPosition;
in vec4 vColor;
out vec4 color;
uniform mat4 ModelViewProjectionMatrix;

subroutine vec4 LightFunc(vec3);

subroutine (LightFunc) vec4 ambient(vec3 n){
    return Materials.ambient;
}

subroutine (LightFunc) vec4 diffuse(vec3 n){
    return Materials.diffuse * max(dot(normalize(n), LightVec.xyz), 0.0);
}

subroutine uniform LightFunc materialShader;

void main(){
    color = vColor;
    gl_position = ModelViewProjectionMatrix * vPosition;
}