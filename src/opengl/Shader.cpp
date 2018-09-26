
#include <Shader.h>

#include "Shader.h"

Shader::Shader(const GLubyte *vertextPath, const GLubyte *fragmentPath) {

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream object can be throw exception
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertextPath);
    }catch (std::ifstream::failure e){

    }

}

void Shader::use() {

}

void Shader::setBool(const std::string &name, bool value) const {

}

void Shader::setInt(const std::string &name, int value) const {

}

void Shader::setFloat(const std::string &name, float value) const {

}

