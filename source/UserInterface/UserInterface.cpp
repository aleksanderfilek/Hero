#include "UserInterface.h"
#include "Widget.h"
#include "../Subsystems/Input/InputSubsystem.h"
#include "../Subsystems/Input/Devices/MouseDevice.h"
#include "../Subsystems/Time/TimeSubsystem.h"
#include "../Graphics/MultiTextureSpritebatch.h"
#include "../Subsystems/Resource/ResourceSubsystem.h"
#include "../Resources/Shader.h"
#include "../Subsystems/Window/WindowObject.h"

UserInterface::UserInterface(class WindowObject* Window)
    : window(Window)
{
    window->OnWindowEventResized.AddEvent(this, &UserInterface::ReactToWindowResized);

    MouseDevice* mouseDevice = (MouseDevice*)InputSubsystem::Get().GetDevice(StringId("Mouse"));
    mouseDevice->OnMouseMotion.AddEvent(this, &UserInterface::ReactToMouseMotion);
    mouseDevice->OnMouseClick.AddEvent(this, &UserInterface::ReactToMouseClick);

    spritebatch = new MultiTextureSpritebatch(100, 32);
    CreateAndRegisterShader();
}

UserInterface::~UserInterface()
{
    for(Widget* widget: widgets)
    {
        delete widget;
    }
    
    delete spritebatch;
}

void UserInterface::Update(float DeltaTime)
{
    for(Widget* widget: widgets)
    {
        widget->Update(DeltaTime);
    }

    spritebatch->Begin();
    for(Widget* widget: widgets)
    {
        widget->Draw(spritebatch);
    }
    spritebatch->End();
}

void UserInterface::ReactToWindowResized(class WindowObject* Window, Int2 Size)
{

}

void UserInterface::ReactToMouseMotion(const Int2& Position, const Int2& MotionVector)
{
    for(Widget* widget: widgets)
    {
        widget->_InternalUpdateHoverState(Position);
    }
}

void UserInterface::ReactToMouseClick(MouseCode Code, InputActionState State)
{
    if(State == InputActionState::RELEASED)
        return;

    for(int i = widgets.Length() - 1; i >= 0; i--)
    {
        bool result = widgets[i]->_InternalUpdateButtonClicks(Code);
        if(result)
            return;
    }
}

void UserInterface::AddWidget(Widget* Widget)
{
    widgets.Add(Widget);
    Widget->Construct();
}

void UserInterface::RemoveWidget(Widget* Widget)
{
    widgets.Remove(Widget);
}

const char* vertexShaderContent = "#version 450\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec2 texCoords;\n"
    "layout (location = 2) in float texIndex;\n"
    "layout (location = 3) in vec4 color;\n"
    "uniform vec2 windowSize;\n"
    "out VS_OUT\n"
    "{\n"
    "    vec2 TexCoords;\n"
    "    float TexIndex;\n"
    "    vec4 Color;\n"
    "} vs_out;\n"
    "void main()\n"
    "{\n"
    "    vs_out.TexCoords = texCoords;\n"
    "    vs_out.TexIndex = texIndex;\n"
    "    vs_out.Color = color;\n"
    "    float x = (position.x * 2.0 / windowSize.x) - 1;"
    "    float y = (position.y * (-2.0) / windowSize.y) + 1;"
    "    gl_Position = pixel * vec4(position, 1.0);\n"
    "}\n\0";

const char* fragmentShaderContent = "#version 450\n"
    "layout (location=0) out vec4 o_Color;\n"
    "layout(binding = 0) uniform sampler2D sb_textures[32];\n"
    "in VS_OUT\n"
    "{\n"
    "    vec2 TexCoords;\n"
    "    float TexIndex;\n"
    "    vec4 Color;\n"
    "} fs_in;\n"
    "void main()\n"
    "{\n"
    "    int index = int(fs_in.TexIndex);\n"
    "    o_Color = texture(sb_textures[index], fs_in.TexCoords) * fs_in.Color;\n"
    "}\n\0";

void UserInterface::CreateAndRegisterShader()
{
    ResourceSubsystem& resourceSubsystem = ResourceSubsystem::Get();
    shader = (Shader*)resourceSubsystem.Get(StringId("UI_Shader"));
    if(shader)
    {
        spritebatch->SetShader(shader);
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

    textures.Add(StringId("framebuffer"), 0);

    shader = new Shader(glId, uniforms, textures);
    resourceSubsystem.Add(StringId("UI_Shader"), shader);
    spritebatch->SetShader(shader);
}
