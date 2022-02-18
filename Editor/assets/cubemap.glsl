#vertex
#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 TexCoords;

void main()
{
  TexCoords = position;
  vec4 pos = proj * view * vec4(position, 1.0);
  gl_Position = pos.xyww;
}
#tessControl

#tessEvaluation

#geometry

#fragment
#version 330 core

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
  gl_FragColor = texture(skybox, TexCoords);
}