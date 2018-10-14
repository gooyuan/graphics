
#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <iostream>
#include <string>
#include <detail/type_mat4x4.hpp>

class Shader{
public:
    // 程序ID
    unsigned int programId;
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    // uniform 工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void setMat4(const std::string &name, glm::mat4 mat);

private:
    void checkCompileError(unsigned int shader, std::string type);
};

#endif