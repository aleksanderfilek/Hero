#include "IntermediateSpriteRenderer.h"
#include "../../ThirdParty/GL/Gl.h"
#include "../../Subsystems/Resource/ResourceSubsystem.h"
#include "../../Resources/Shader.h"
#include "../../Resources/Texture.h"
#include "../../Resources/Mesh.h"

const StringId meshId = StringId("M_Plane");
const StringId shaderId = StringId("S_IntermediateSpriteRenderer");
const StringId windowSizeId = StringId("windowSize");
const StringId positionId = StringId("position");
const StringId sizeId = StringId("size");
const StringId rectId = StringId("rect");
const StringId colorId = StringId("color");

IntermediateSpriteRenderer::IntermediateSpriteRenderer()
{
    CreateAndRegisterShader();
    CreateAndRegisterPlaneMesh();
}

IntermediateSpriteRenderer::~IntermediateSpriteRenderer()
{

}

void IntermediateSpriteRenderer::Start(const Int2& WindowSize)
{
    Float2 size((float)WindowSize.X, (float)WindowSize.Y);
    shader->Bind();
    shader->SetFloat2(windowSizeId, size);
}

void IntermediateSpriteRenderer::End()
{
}

void IntermediateSpriteRenderer::DrawTexture(class Texture* Texture, const Int2& Position, const Int2& Size)
{ 
    Texture->Bind();
    shader->SetFloat2(positionId, { (float)Position.X, (float)Position.Y });
    shader->SetFloat2(sizeId, { (float)Size.X, (float)Size.Y });
    shader->SetFloat4(rectId, { 0.0f, 0.0f, 1.0f, 1.0f });
    shader->SetFloat4(colorId, { 1.0f, 1.0f, 1.0f, 1.0f });
    mesh->Draw();
}

void IntermediateSpriteRenderer::DrawTextureEx(class Texture* Texture, const Int2& Position, const Int2& Size, const Float4& Rect, Color Color)
{
    Texture->Bind();
    shader->SetFloat2(positionId, { (float)Position.X, (float)Position.Y });
    shader->SetFloat2(sizeId, { (float)Size.X, (float)Size.Y });
    shader->SetFloat4(rectId, Rect);
    shader->SetFloat4(colorId, Color.ToFloat4());
    mesh->Draw();
}

const char* vertexShaderContent =
    "#version 450\n"
    "layout (location = 0) in vec2 v_position;\n"
    "layout (location = 1) in vec2 v_texCoords;\n"
    "uniform vec2 windowSize;\n"
    "uniform vec2 position;\n"
    "uniform vec2 size;\n"
    "uniform vec4 rect;\n"
    "uniform vec4 color;\n"
    "out VS_OUT\n"
    "{\n"
    "    vec2 TexCoords;\n"
    "    vec4 Color;\n"
    "} vs_out;\n"
    "void main()\n"
    "{\n"
    "    vec2 normalizedPosition = v_position + vec2(1.0,-1.0);\n"
    "    normalizedPosition /= 2.0;\n"
    "    normalizedPosition.y = normalizedPosition.y * -1.0;\n"
    "    vec2 pixelPosition;\n"
    "    pixelPosition.x = normalizedPosition.x * size.x + position.x;\n"
    "    pixelPosition.y = normalizedPosition.y * size.y + position.y;\n"
    "    float x = (pixelPosition.x * 2.0 / windowSize.x) - 1;"
    "    float y = (pixelPosition.y * (-2.0) / windowSize.y) + 1;"
    "    gl_Position = vec4(x, y, 0.0, 1.0);\n"
    "    vec2 texCoords;\n"
    "    vec2 rectDiff = rect.zw - rect.xy;\n"
    "    texCoords.x = normalizedPosition.x * rectDiff.x + rect.x;\n"
    "    texCoords.y = normalizedPosition.y * rectDiff.y + rect.y;\n"
    "    vs_out.TexCoords = texCoords;\n"
    "    vs_out.Color = color;\n"
    "}\n\0";

const char* fragmentShaderContent = 
    "#version 450\n"
    "layout (location = 0) out vec4 o_Color;\n"
    "uniform sampler2D baseTexture;\n"
    "in VS_OUT\n"
    "{\n"
    "    vec2 TexCoords;\n"
    "    vec4 Color;\n"
    "} fs_in;\n"
    "void main()\n"
    "{\n"
    "	o_Color = texture(baseTexture, fs_in.TexCoords) * fs_in.Color;\n"
    "}\n\0";

void IntermediateSpriteRenderer::CreateAndRegisterShader()
{
    ResourceSubsystem& resourceSubsystem = ResourceSubsystem::Get();
    shader = (Shader*)resourceSubsystem.Get(shaderId);
    if (shader)
    {
        return;
    }

    uint32_t glId;
    Map<StringId, uint32_t> uniforms;
    Map<StringId, uint32_t> textures;

    glId = glCreateProgram();

    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderContent, nullptr);
    glCompileShader(vertexShader);
    GlShaderCheckError(vertexShader, GL_COMPILE_STATUS);
    glAttachShader(glId, vertexShader);
    GlProgramCheckError(glId, GL_ATTACHED_SHADERS);

    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderContent, nullptr);
    glCompileShader(fragmentShader);
    GlShaderCheckError(fragmentShader, GL_COMPILE_STATUS);
    glAttachShader(glId, fragmentShader);
    GlProgramCheckError(glId, GL_ATTACHED_SHADERS);

    glLinkProgram(glId);

    glDeleteShader(vertexShader);
    GlShaderCheckError(vertexShader, GL_DELETE_STATUS);

    glDeleteShader(fragmentShader);
    GlShaderCheckError(fragmentShader, GL_DELETE_STATUS);

    glUseProgram(glId);
    textures.Add(StringId("baseTexture"), 0);

    uniforms.Add(windowSizeId, glGetUniformLocation(glId, "windowSize"));    
    uniforms.Add(positionId, glGetUniformLocation(glId, "position"));
    uniforms.Add(sizeId, glGetUniformLocation(glId, "size"));
    uniforms.Add(rectId, glGetUniformLocation(glId, "rect"));
    uniforms.Add(colorId, glGetUniformLocation(glId, "color"));

    shader = new Shader(glId, uniforms, textures);
    resourceSubsystem.Add(shaderId, shader, StringId("Shader"));
}

void IntermediateSpriteRenderer::CreateAndRegisterPlaneMesh()
{
    ResourceSubsystem& resourceSubsystem = ResourceSubsystem::Get();
    mesh = (Mesh*)resourceSubsystem.Get(meshId);
    if (mesh)
    {
        return;
    }

    Array<MeshBuffer<float>> buffers;

    MeshBuffer<float> positions;
    positions.Type = BufferType::VEC2;
    positions.Array = new float[8] { -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f };
    positions.Length = 8;
    buffers.Add(positions);

    MeshBuffer<float> texCoords;
    texCoords.Type = BufferType::VEC2;
    texCoords.Array = new float[8] { 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
    texCoords.Length = 8;
    buffers.Add(texCoords);

    MeshBuffer<int> indicies;
    indicies.Type = BufferType::SINGLE;
    indicies.Array = new int[6] { 0, 1, 2, 1, 3, 2};
    indicies.Length = 6;

    mesh = new Mesh(buffers, indicies);
    resourceSubsystem.Add(meshId, mesh, StringId("Mesh"));
}