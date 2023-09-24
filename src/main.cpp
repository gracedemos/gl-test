#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "utils.h"
#include "Shader.h"

int main() {
    if (glfwInit() != GLFW_TRUE) {
        std::cerr << "Failed to init glfw\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GL Test", nullptr, nullptr);

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            isPaused ^= true;
        }
    });

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    gladLoadGL();

    const uint8_t* deviceName = glGetString(GL_RENDERER);

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    GLuint vao[2], vbo[2], ebo;
    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PRISM_VERTICES), PRISM_VERTICES, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PLANE_VERTICES), PLANE_VERTICES, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PLANE_INDICES), PLANE_INDICES, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::string defaultVert = Shader::getShaderPath("default.vert");
    std::string defaultFrag = Shader::getShaderPath("default.frag");
    Shader defaultShader(defaultVert, defaultFrag);

    float clearColor[] = {
            0.1f, 0.1f, 0.1f, 1.0f
    };
    glEnable(GL_DEPTH_TEST);

    glm::mat4 prismModel = glm::mat4(1.0f);
    glm::mat4 planeModel = glm::mat4(1.0f);

    planeModel = glm::translate(planeModel, glm::vec3(0.0f, -0.75f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.5f));

    const glm::vec3 prismAmbient = glm::vec3(0.0f, 0.2f, 0.2f);
    const glm::vec3 prismColor = glm::vec3(0.0f, 0.5f, 0.5f);
    const glm::vec3 planeAmbient = glm::vec3(0.2f, 0.2f, 0.0f);
    const glm::vec3 planeColor = glm::vec3(0.5f, 0.25f, 0.0f);

    float lastFrameTime;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        float deltaTime = static_cast<float>(glfwGetTime()) - lastFrameTime;
        lastFrameTime = static_cast<float>(glfwGetTime());

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glfwGetWindowSize(window, &width, &height);

        proj = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
        prismModel = glm::rotate(prismModel, glm::radians(45.0f) * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));

        handleInput(window, &view, deltaTime);

        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        defaultShader.use();
        glBindVertexArray(vao[0]);

        defaultShader.uniformMat4("model", glm::value_ptr(prismModel));
        defaultShader.uniformMat4("view", glm::value_ptr(view));
        defaultShader.uniformMat4("proj", glm::value_ptr(proj));

        defaultShader.uniformVec3("ambient", glm::value_ptr(prismAmbient));
        defaultShader.uniformVec3("baseColor", glm::value_ptr(prismColor));

        glDrawArrays(GL_TRIANGLES, 0, sizeof(PRISM_VERTICES) / sizeof(GLfloat) / 3);
        glBindVertexArray(0);

        glBindVertexArray(vao[1]);

        defaultShader.uniformMat4("model", glm::value_ptr(planeModel));

        defaultShader.uniformVec3("ambient", glm::value_ptr(planeAmbient));
        defaultShader.uniformVec3("baseColor", glm::value_ptr(planeColor));

        glDrawElements(GL_TRIANGLES, sizeof(PLANE_INDICES) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(300, 100));
        ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::Text("GPU: %s", deviceName);
        ImGui::Text("Delta Time: %f", deltaTime);
        ImGui::Text("FPS: %d", static_cast<int>(1.0f / deltaTime));
        ImGui::End();

        if (isPaused) {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(width)));
            ImGui::Begin("GL Test", &isPaused,
                         ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoCollapse);
            if (ImGui::CollapsingHeader("Clear Color")) {
                ImGui::PushItemWidth(static_cast<float>(width) * 0.25f);
                ImGui::ColorPicker3("Clear Color", clearColor);
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button("Reset")) {
                    clearColor[0] = 0.1f;
                    clearColor[1] = 0.1f;
                    clearColor[2] = 0.1f;
                }
                ImGui::Spacing();
                ImGui::Separator();
            }
            ImGui::Spacing();
            if (ImGui::Button("Quit")) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
