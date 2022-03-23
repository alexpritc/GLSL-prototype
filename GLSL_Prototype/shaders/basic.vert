#version 460

layout (location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;
layout (location = 3) in vec3 VertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Color;
out vec3 FragPos;
out vec3 Normal;
out vec2 UV;

void main()
{
    FragPos = vec3(model * vec4(VertexPosition, 1.0));
    gl_Position = projection * view * vec4(FragPos, 1.0);

    Color = VertexColor;
    Normal = vertexNormal;
    UV = vertexUV;
}
