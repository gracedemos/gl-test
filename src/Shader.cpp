//
// Created by Grace Demos on 9/22/23.
//

#include <fstream>
#include <iostream>

#ifdef linux
#include <unistd.h>
#endif

#include "Shader.h"

Shader::Shader(std::string &vertPath, std::string &fragPath) {
    const char* vertSource = readShaderSource(vertPath.c_str());
    const char* fragSource = readShaderSource(fragPath.c_str());
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
    delete[] vertSource;
    delete[] fragSource;
}

const char * Shader::readShaderSource(const char *path) {
    std::ifstream file(path, std::ios::binary | std::ios::in);
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* source = new char[size + 1];
    file.read(source, size);
    file.close();
    source[size] = '\x00';

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

std::string Shader::getShaderPath(const char *shader) {
    std::string path;
    path.resize(255);
    size_t size = readlink("/proc/self/exe", path.data(), 255);
    path.resize(size);
    path.erase(size - 25, 25);
    path += "shaders/";
    path += shader;
    return path;
}
