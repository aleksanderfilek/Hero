#vertex
#version 450 core
layout (location = 0) in vec3 position;

uniform mat4 model;

layout (std140, binding = 0) uniform Matrices
{
    mat4 view;
    mat4 projection;
    mat4 pixel;
};

out VS_OUT
{
  vec3 TexCoords;
} vs_out;

void main()
{
  vs_out.TexCoords = position;
  vec4 pos = projection * view * vec4(position, 1.0);
  gl_Position = pos.xyww;
}
#tessControl

#tessEvaluation

#geometry

#fragment
#version 450 core

in VS_OUT
{
  vec3 TexCoords;
} fs_in;

uniform samplerCube skybox;

void main()
{
  gl_FragColor = texture(skybox, fs_in.TexCoords);
}