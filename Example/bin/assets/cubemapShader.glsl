#vertex
#version 450

layout (location = 0) in vec3 position;

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
  vec4 pos = projection * mat4(mat3(view)) * vec4(position, 1.0);
  gl_Position = pos.xyww;
}

#tessControl

#tessEvaluation

#geometry

#fragment
#version 450

layout (location = 0) out vec4 o_Color;

in VS_OUT
{
  vec3 TexCoords;
} fs_in;

uniform samplerCube skybox;

void main()
{
  o_Color = texture(skybox, fs_in.TexCoords);
}