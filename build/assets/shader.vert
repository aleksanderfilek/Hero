#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float texIndex;
layout (location = 3) in vec4 color;

uniform mat4 view;

out vec2 TexCoords;
out float TexIndex;
out vec4 Color;

void main()
{
    TexCoords = texCoords;
    TexIndex = texIndex;
    Color = color;
    gl_Position = view * vec4(position, 1.0);
}