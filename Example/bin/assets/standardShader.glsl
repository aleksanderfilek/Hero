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
  vec2 Uv;
  vec3 TangentLightDir;
  vec3 TangentViewDir;
  vec3 vLightColor;
} vs_out;

uniform mat4 model;

void main()
{
  vs_out.vLightColor = LightColor;

  vec3 T = normalize(mat3(transpose(inverse(model))) * normal);
  vec3 N = normalize(vec3(model * vec4(normal, 0.0)));
  T = normalize(T - dot(T, N) * N);
  vec3 B = cross(N, T);
  mat3 TBN = transpose(mat3(T, B, N));

  vs_out.TangentLightDir = TBN * normalize(-LightDirection);

  vec3 fragPos = vec3(model * vec4(position, 1.0));
  vs_out.TangentViewDir  = TBN * normalize(viewPos - fragPos);

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
  vec2 Uv;
  vec3 TangentLightDir;
  vec3 TangentViewDir;
  vec3 vLightColor;
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

  vec3 color = texture(baseTex, fs_in.Uv).rgb;
  vec3 roughness = texture(roughnessTex, fs_in.Uv).rgb;

  vec3 ambient = ambientStrength * color;

  vec3 lightDir = fs_in.TangentLightDir;
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = diff * color;

  vec3 viewDir = fs_in.TangentViewDir;
  vec3 reflectDir = reflect(-lightDir, normal); 
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
  vec3 specular = vec3(specularStrength) * spec * roughness;

  vec3 result = ambient + diffuse + specular;
  o_Color = vec4(result, 1.0);
}