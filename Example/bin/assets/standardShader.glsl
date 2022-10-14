#vertex
#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;  

layout (std140, binding = 0) uniform Matrices
{
  mat4 view;
  mat4 projection;
  mat4 pixel;
  vec3 viewPos;
};

layout (std140, binding = 1) uniform DirectionalSun
{
  vec3 LightColor;
  vec3 LightDirection;
};

out VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec3 ViewPos;
  vec2 Uv;
  mat3 TBN;
  vec3 vLightColor;
  vec3 vLightDirection;
} vs_out;

uniform mat4 model;

void main()
{
  vs_out.vLightColor = LightColor;
  vs_out.vLightDirection = LightDirection;

  vec3 T = normalize(mat3(transpose(inverse(model))) * normal);
  vec3 N = normalize(vec3(model * vec4(normal, 0.0)));
  vec3 B = cross(N, T);
  mat3 TBN = transpose(mat3(T, B, N));
  vs_out.TBN = TBN;
  vs_out.ViewPos = viewPos;
  vs_out.Normal = mat3(transpose(inverse(model))) * normal;
  vs_out.FragPos = vec3(model * vec4(position, 1.0));
  vs_out.Uv = vec2(uv.x, 1.0 - uv.y);
  gl_Position = projection * view * model * vec4(position, 1.0);
}

#tessControl

#tessEvaluation

#geometry

#fragment
#version 450

layout (location = 0) out vec4 o_Color;

in VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec3 ViewPos;
  vec2 Uv;
  mat3 TBN;
  vec3 vLightColor;
  vec3 vLightDirection;
} fs_in;

layout(binding = 0) uniform sampler2D baseTex;
layout(binding = 1) uniform sampler2D normalTex;
layout(binding = 2) uniform sampler2D roughnessTex;
uniform float ambientStrength;
uniform float specularStrength;

void main()
{
  vec3 normal = texture(normalTex, fs_in.Uv).rgb;
  normal = normal * 2.0 - 1.0;   
  normal = normalize(normal); 

  vec3 lightDir = fs_in.TBN * normalize(-fs_in.vLightDirection);  
  vec3 viewDir = fs_in.TBN * normalize(fs_in.ViewPos - fs_in.FragPos);

  vec3 ambient = ambientStrength * fs_in.vLightColor;

  float diff = max(dot(normal, lightDir), 0.0);
  vec3 diffuse = diff * texture(baseTex, fs_in.Uv).rgb;

  vec3 reflectDir = reflect(-lightDir, normal); 
  float spec = max(pow(dot(viewDir, reflectDir), 5.0), 0.0);
  vec3 specular = specularStrength * spec * fs_in.vLightColor * texture(roughnessTex, fs_in.Uv).rgb;

  vec3 result = ambient + diffuse + specular;
  o_Color = vec4(result, 1.0);
}