#version 450

layout (location = 0) out vec4 o_Color;

in vec2 TexCoords;
in float TexIndex;
in vec4 Color;

uniform sampler2D sb_textures[32];

void main()
{
    int index = int(TexIndex);
    o_Color = texture(sb_textures[index], TexCoords) * Color;
}