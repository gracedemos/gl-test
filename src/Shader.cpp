//
// Created by Grace Demos on 9/22/23.
//

#include <fstream>
#include <iostream>

#include "Shader.h"

Shader::Shader(const char *vertPath, const char *fragPath) {
    char* vertSource = readShaderSource(vertPath);
    char* fragSource = readShaderSource(fragPath);
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertShader, 1, &vertSource, nullptr);
    glShaderSource(fragShader, 1, &fragSource, nullptr);
    glCompileShader(vertShader);
    glCompileShader(fragShader);

    id = glCreateProgram();
    glAttachShader(id, vertShader);
    glAttachShader(id, fragShader);
    glLinkProgram(id);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    delete vertSource;
    delete fragSource;
}

char* Shader::readShaderSource(const char *path) {
    std::ifstream file(path, std::ios::binary | std::ios::in);
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* source = new char[size];
    file.read(source, size);
    file.close();

    return source;
}

void Shader::use() const {
    glUseProgram(id);
}

void Shader::uniformMat4(const char *name, const float *data) const {
    GLint location = glGetUniformLocation(id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, data);
}

void Shader::uniformVec3(const char *name, const float *data) const {
    GLint location = glGetUniformLocation(id, name);
    glUniform3fv(location, 1, data);
}
