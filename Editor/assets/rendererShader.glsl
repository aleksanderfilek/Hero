#vertex
#version 450

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out VS_OUT
{
    vec2 TexCoords;
} vs_out;

void main()
{
    vs_out.TexCoords = texCoords;
    gl_Position = vec4(position, 0.0, 1.0);
}

#tessControl

#tessEvaluation

#geometry

#fragment
#version 450

layout (location=0) out vec4 o_Color;

uniform sampler2D baseTex;

in VS_OUT
{
    vec2 TexCoords;
} fs_in;

void main()
{
    o_Color = texture(baseTex, fs_in.TexCoords);
}