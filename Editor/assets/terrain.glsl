#vertex
#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 view;
uniform mat4 proj;
out float y;
void main()
{
  gl_Position = proj * view * vec4(position, 1.0);
  y = position.y;
}
#tessControl

#tessEvaluation

#geometry

#fragment
#version 330 core

in float y;

void main()
{
  float col = y;
  col *= 4.0;
  col /= 255.0;
  gl_FragColor = vec4(col, col, col, 1.0);
}