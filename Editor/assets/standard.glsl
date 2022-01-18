#vertex
#version 330 core
layout (location = 0) in vec2 position;
void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
}
#tessControl

#tessEvaluation

#geometry

#fragment
void main()
{
  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}