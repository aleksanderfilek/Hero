#vertex
#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 model;

layout (std140, binding = 0) uniform Matrices
{
    mat4 view;
    mat4 projection;
    mat4 pixel;
};

out VS_OUT
{
  vec2 TexCoord;
} vs_out;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vs_out.TexCoord = vec2(texCoord.x, 1 - texCoord.y);
}
#tessControl

#tessEvaluation

#geometry

#fragment
#version 450 core

uniform sampler2D ourTexture;

in VS_OUT
{
  vec2 TexCoord;
} fs_in;

void main()
{
  gl_FragColor = texture(ourTexture, fs_in.TexCoord);
}