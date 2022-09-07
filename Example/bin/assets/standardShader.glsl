#vertex
#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

layout (std140, binding = 0) uniform Matrices
{
  mat4 view;
  mat4 projection;
  mat4 pixel;
  vec3 viewPos;
};

out VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec3 ViewPos;
} vs_out;

uniform mat4 model;

void main()
{
  vs_out.ViewPos = viewPos;
  vs_out.Normal = mat3(transpose(inverse(model))) * normal;
  vs_out.FragPos = vec3(model * vec4(position, 1.0));
  gl_Position = projection * view * model * vec4(position, 1.0);
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
  vec3 LightPos;
};

in VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec3 ViewPos;
} fs_in;

void main()
{
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * LightColor;

  vec3 norm = normalize(fs_in.Normal);
  vec3 lightDir = normalize(LightPos - fs_in.FragPos);  

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * LightColor;

  float specularStrength = 0.5;
  vec3 viewDir = normalize(fs_in.ViewPos - fs_in.FragPos);
  vec3 reflectDir = reflect(-lightDir, norm); 

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * LightColor;

  vec3 result = (ambient + diffuse + specular) * vec3(1.0, 1.0, 1.0);
  o_Color = vec4(result, 1.0);
}