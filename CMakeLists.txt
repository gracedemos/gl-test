cmake_minimum_required(VERSION 3.26)
project(gl-test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)

include_directories(${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/imgui
        ${CMAKE_SOURCE_DIR}/imgui/backends
		${CMAKE_SOURCE_DIR}/glm
        ${GLFW3_INCLUDE_DIRS})

add_executable(gl-test src/main.cpp
        src/glad.c
        src/utils.h
        src/Shader.cpp
        src/Shader.h
        src/utils.cpp
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp)
target_link_libraries(gl-test ${GLFW3_LIBRARIES})
