#vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
out vec2 TexCoord;
void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0);
    TexCoord = vec2(texCoord.x, 1 - texCoord.y);
}
#tessControl

#tessEvaluation

#geometry

#fragment
#version 330 core
in vec2 TexCoord;
uniform sampler2D ourTexture;
void main()
{
  gl_FragColor = texture(ourTexture, TexCoord);
}