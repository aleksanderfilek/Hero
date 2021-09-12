#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float texIndex;

uniform mat4 view;

out vec2 TexCoords;
out float TexIndex;

void main()
{
    TexCoords = texCoords;
    TexIndex = texIndex;
    gl_Position = view * vec4(position, 1.0);
}