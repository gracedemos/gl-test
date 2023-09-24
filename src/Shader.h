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
    Shader(const char* vertPath, const char* fragPath);
    void use() const;
    void uniformMat4(const char* name, const float* data) const;
    void uniformVec3(const char* name, const float* data) const;

private:
    static char* readShaderSource(const char* path);
};

#endif //GL_TEST_SHADER_H
