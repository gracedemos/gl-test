//
// Created by Grace Demos on 9/22/23.
//

#include <GLFW/glfw3.h>

#include "utils.h"

void handleInput(GLFWwindow *window, glm::mat4 *view, float deltaTime) {
    auto moveVec = glm::vec3(0.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_W)) {
        moveVec.z = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        moveVec.z = -1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        moveVec.x = -1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        moveVec.x = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        moveVec.y = -1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        moveVec.y = 1.0f;
    }

    if (moveVec.x == 0.0f && moveVec.y == 0.0f && moveVec.z == 0.0f) {
        return;
    }

    moveVec = glm::normalize(moveVec) * deltaTime * 5.0f;
    *view = glm::translate(*view, moveVec);
}
