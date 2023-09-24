#version 330

struct V2F {
    vec3 position;
    vec3 normal;
};

in V2F v2f;

out vec4 fragColor;

uniform vec3 ambient;
uniform vec3 baseColor;

void main() {
    const vec3 lightPos = vec3(0.0, 0.3, 1.0);

    vec3 lightDir = normalize(lightPos - v2f.position);
    float diffuse = max(0.0, dot(lightDir, v2f.normal));
    vec3 color = (ambient + diffuse) * baseColor;

    fragColor = vec4(color, 1.0);
}