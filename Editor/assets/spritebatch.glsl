#vertex
#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float texIndex;
layout (location = 3) in vec4 color;
layout (location = 4) in float layer;

layout (std140, binding = 0) uniform Matrices
{
    mat4 view;
    mat4 projection;
    mat4 pixel;
};

out VS_OUT
{
    vec2 TexCoords;
    float TexIndex;
    vec4 Color;
} vs_out;

void main()
{
    vs_out.TexCoords = texCoords;
    vs_out.TexIndex = texIndex;
    vs_out.Color = color;
    gl_Position = pixel * vec4(position, 1.0);
    gl_Position.z = layer / 256.0;
}

#tessControl

#tessEvaluation

#geometry

#fragment
#version 450

layout (location=0) out vec4 o_Color;

uniform sampler2D sb_textures[32];

in VS_OUT
{
    vec2 TexCoords;
    float TexIndex;
    vec4 Color;
} fs_in;

void main()
{
	int index = int(fs_in.TexIndex);
	o_Color = texture(sb_textures[index], fs_in.TexCoords) * fs_in.Color;
}
