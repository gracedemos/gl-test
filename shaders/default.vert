#version 330

struct V2F {
    vec3 position;
    vec3 normal;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out V2F v2f;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    v2f.position = vec3(model * vec4(aPos, 1.0));
    v2f.normal = normalize(mat3(model) * aNormal);
}