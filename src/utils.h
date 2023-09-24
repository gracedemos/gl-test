//
// Created by Grace Demos on 9/22/23.
//

#ifndef GL_TEST_UTILS_H
#define GL_TEST_UTILS_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static bool isPaused = false;

static const GLfloat PRISM_VERTICES[] = {
        0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 1.0f, // Front
        -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 1.0f,

        0.0f, 0.5f, -0.5f, -1.0f, 0.25f, -0.5f, // Left
        -0.5f, -0.5f, 0.0f, -1.0f, 0.25f, -0.5f,
        0.0f, -0.5f, -1.0f, -1.0f, 0.25f, -0.5f,

        0.0f, 0.5f, -0.5f, 1.0f, 0.25f, -0.5f, // Right
        0.0f, -0.5f, -1.0f, 1.0f, 0.25f, -0.5f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.25f, -0.5f,

        -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, // Bottom
        0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, -0.5f, -1.0f, 0.0f, -1.0f, 0.0f
};

static const GLfloat PLANE_VERTICES[] = {
        -1.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f
};

static const GLuint PLANE_INDICES[] = {
        0, 1, 2,
        2, 1, 3
};

void handleInput(GLFWwindow *window, glm::mat4 *view, float deltaTime);

#endif //GL_TEST_UTILS_H
