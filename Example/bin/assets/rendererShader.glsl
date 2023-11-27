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
    gl_Position = vec4(position, 0.1, 1.0);
}

#tessControl

#tessEvaluation

#geometry

#fragment
#version 450

layout (location=0) out vec4 o_Color;

layout(binding = 0) uniform sampler2D colorTex;
layout(binding = 1) uniform sampler2D idTex;

uniform int id;

in VS_OUT
{
    vec2 TexCoords;
} fs_in;

void main()
{
    if(id == 0)
    {
        o_Color = texture(colorTex, fs_in.TexCoords);
    }
    else
    {
        o_Color = texture(idTex, fs_in.TexCoords);
    }
}