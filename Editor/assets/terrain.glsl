#vertex
#version 450 core
layout (location = 0) in vec3 position;

layout (std140, binding = 0) uniform Matrices
{
    mat4 view;
    mat4 projection;
    mat4 pixel;
};

out VS_OUT
{
  float y;
} vs_out;

void main()
{
  gl_Position = projection * view * vec4(position, 1.0);
  vs_out.y = position.y;
}
#tessControl

#tessEvaluation

#geometry

#fragment
#version 450 core

in VS_OUT
{
  float y;
} fs_in;

void main()
{
  float col = fs_in.y;
  col *= 4.0;
  col /= 255.0;
  gl_FragColor = vec4(col, col, col, 1.0);
}