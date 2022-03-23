#version 460

layout (location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

layout (location = 3) in vec3 ambientColor;
layout (location = 4) in vec3 diffuseColor;
layout (location = 5) in vec3 specularColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 color;
out vec3 fragPos;
out vec3 normal;
out vec2 UV;

out vec3 Ka;
out vec3 Kd;
out vec3 Ks;

void main()
{
    fragPos = vec3(model * vec4(vertexPosition, 1.0));
    gl_Position = projection * view * vec4(fragPos, 1.0);

    normal = vertexNormal;
    UV = vertexUV;

    Ka = ambientColor;
  	Kd = diffuseColor;
    Ks = specularColor;
}
