#vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0);
}
#tessControl

#tessEvaluation

#geometry

#fragment
void main()
{
  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}