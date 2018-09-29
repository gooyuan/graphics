
#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <iostream>
#include <string>

class Shader{
public:
    // 程序ID
    unsigned int programId;

    // todo char -> GLChar
    Shader(const char* vertextPath, const char* fragmentPath);

    void use();

    // uniform 工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    void checkCompileError(unsigned int shader, std::string type);
};

#endif