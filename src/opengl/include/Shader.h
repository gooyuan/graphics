
#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <GL/gl.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class Shader{
public:
    // 程序ID
    unsigned int programId;

    // todo char -> GLChar
    Shader(const GLubyte * vertextPath, const GLubyte * fragmentPath);

    void use();

    // uniform 工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif