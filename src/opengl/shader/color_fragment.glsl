#version 330 core
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

float ambientStrength = 0.1f;

in vec3 FragPos;
in vec3 Normal;
void main()
{
    vec3 ambient = ambientStrength * lightColor;
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuse = max(dot(norm, lightDir), 0.0f);

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0f);
}