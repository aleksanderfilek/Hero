#vertex
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

#tessControl

#tessEvaluation

#geometry

#fragment
#version 450

layout (location=0) out vec4 o_Color;

in vec2 TexCoords;
in float TexIndex;
in vec4 Color;

uniform sampler2D sb_textures[32];

void main()
{
	int index = int(TexIndex);
	o_Color = texture(sb_textures[index], TexCoords) * Color;
}
