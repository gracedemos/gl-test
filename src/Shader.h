//
// Created by Grace Demos on 9/22/23.
//

#ifndef GL_TEST_SHADER_H
#define GL_TEST_SHADER_H

#include <glad/glad.h>
#include <string>

class Shader {
private:
    GLuint id;

public:
    Shader(std::string &vertPath, std::string &fragPath);
    void use() const;
    void uniformMat4(const char* name, const float* data) const;
    void uniformVec3(const char* name, const float* data) const;

    static std::string getShaderPath(const char* shader);

private:
    static const char * readShaderSource(const char* path);
};

#endif //GL_TEST_SHADER_H
