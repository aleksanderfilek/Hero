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

layout (std140, binding = 1) uniform DirectionalSun
{
  vec3 LightColor;
  vec3 LightDirection;
};

out VS_OUT
{
  vec2 Uv;
  vec3 vLightColor;
  vec3 Normal;
  mat4 ModelMat;
  vec3 LightDir;
  vec3 Position;
} vs_out;

uniform mat4 model;

void main()
{
  vs_out.vLightColor = LightColor;
  vs_out.Uv = vec2(uv.x, 1.0 - uv.y);
  vs_out.Normal = normal;
  vs_out.ModelMat = model;
  vs_out.LightDir = -LightDirection;
  vs_out.Position = position;
  gl_Position = projection * view * model * vec4(position, 1.0);
}

#tessControl

#tessEvaluation

#geometry
#version 450
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

layout (std140, binding = 0) uniform Matrices
{
  mat4 view;
  mat4 projection;
  mat4 pixel;
  vec3 viewPos;
};

in VS_OUT
{
  vec2 Uv;
  vec3 vLightColor;
  vec3 Normal;
  mat4 ModelMat;
  vec3 LightDir;
  vec3 Position;
} gs_in[3];

out VS_OUT
{
  vec2 Uv;
  vec3 TangentLightDir;
  vec3 TangentViewDir;
  vec3 vLightColor;
} gs_out;

void Generate(int index, vec3 tangent)
{

  vec3 T = normalize(vec3(gs_in[index].ModelMat * vec4(tangent, 0.0)));
  vec3 N = normalize(vec3(gs_in[index].ModelMat * vec4(gs_in[index].Normal, 0.0)));
  T = normalize(T - dot(T, N) * N);
  vec3 B = cross(N, T);
  mat3 TBN = transpose(mat3(T, B, N));

  gs_out.TangentLightDir = TBN * normalize(gs_in[index].LightDir);

  vec3 fragPos = vec3(gs_in[index].ModelMat * vec4(gs_in[index].Position, 1.0));
  gs_out.TangentViewDir  = TBN * normalize(viewPos - fragPos);

  gl_Position = gl_in[index].gl_Position;
  gs_out.Uv = gs_in[index].Uv;
  gs_out.vLightColor = gs_in[index].vLightColor;
  EmitVertex();
}

void main()
{
  vec3 edge1 = gs_in[1].Position - gs_in[0].Position;
  vec3 edge2 = gs_in[2].Position - gs_in[0].Position;
  vec2 deltaUV1 = gs_in[1].Uv - gs_in[0].Uv;
  vec2 deltaUV2 = gs_in[2].Uv - gs_in[0].Uv;
  float f = 1.0 / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

  float tangentx = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
  float tangenty = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
  float tangentz = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

  vec3 tangent = vec3(tangentx, tangenty, tangentz);

  Generate(0, tangent);
  Generate(1, tangent);
  Generate(2, tangent);
}

#fragment
#version 450

layout (location = 0) out vec4 o_Color;
layout (location = 1) out vec4 o_Id;

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

uniform vec4 id;

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
  o_Id = id;
}