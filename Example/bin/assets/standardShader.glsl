#vertex
#version 450

layout (location = 0) in vec3 position;

layout (std140, binding = 0) uniform Matrices
{
  mat4 view;
  mat4 projection;
  mat4 pixel;
};

void main()
{
  gl_Position = projection * view * vec4(position, 1.0);
}

#tessControl

#tessEvaluation

#geometry

#fragment
#version 450

layout (location = 0) out vec4 o_Color;

layout (std140, binding = 1) uniform DirectionalSun
{
  vec3 LightColor;
};

void main()
{
  o_Color = vec4(LightColor * vec3(1.0, 0.0, 0.0), 1.0);
}