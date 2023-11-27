#include "WindowSubsystem.h"
#include "../../ThirdParty/SDL2/SDL.h"
#include "../../ThirdParty/GL/Gl.h"
#include "../../ThirdParty/SDL2/SDL_opengl.h"
#include "WindowObject.h"
#include "../../Core.h"
#include "../../Resources/Mesh.h"
#include "../../Resources/Shader.h"

WindowSubsystem* WindowSubsystem::instance = nullptr;

WindowSubsystem::WindowSubsystem(const StringId& Id, const WindowConfiguration& WindowConfig)
{
    instance = this;
    updateEnabled = true;

    CreateWindow(Id, WindowConfig);
}

void WindowSubsystem::Startup()
{
    Subsystem::Startup();

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        exit(-1);
    }

    GetSubsystemManager()->GetEvent(inputEventId).AddEvent(this, &WindowSubsystem::HandleEvent);

    for(const auto& windowConfiguration: windowsConfigurationsToCreate)
    {
        CreateWindow(windowConfiguration.first, windowConfiguration.second);
    }
    windowsConfigurationsToCreate.Clear();

    CreateScreenMesh();
    CreateScreenShader();
}

void WindowSubsystem::Shutdown()
{
    Subsystem::Shutdown();

    for(WindowObject* window: windowObjects)
    {
        delete window;
    }

    SDL_Quit();

    delete screenMesh;
    delete screenShader;
}

void WindowSubsystem::Update()
{
    Subsystem::Update();
    for(WindowObject* window: windowObjects)
    {
        window->Render();
    }
}

void WindowSubsystem::ReactToWindowFocusGained(class WindowObject* Window)
{
    currentWidnow = Window;
}

void WindowSubsystem::ReactToWindowFocusLost(class WindowObject* Window)
{
    currentWidnow = nullptr;
}

class WindowObject* WindowSubsystem::CreateWindow(const StringId& Id, const WindowConfiguration& WindowConfig)
{
    if(!IsStarted())
    {
        windowsConfigurationsToCreate.Add({Id, WindowConfig});
        return nullptr;
    }
    WindowObject* window = new WindowObject(Id, WindowConfig, this);
    windowObjects.Add(window);

    if(!currentWidnow)
    {
        currentWidnow = window;
    }

    return window;
}

void WindowSubsystem::CloseWindow(class WindowObject* Window)
{
    if(windowObjects.Length() == 1)
    {
        Core::Get().Stop();
        return;
    }

    bool result = windowObjects.Remove(Window);
    if(!result)
    {
        return;
    }

    delete Window;
}

void WindowSubsystem::HandleEvent(void* Data)
{
    SDL_Event* event = (SDL_Event*)Data;

    //if(event->type != SDL_WINDOWEVENT)
    //{
    //    return;
    //} 

    for(WindowObject* window: windowObjects)
    {
        /*if(event->window.windowID == window->GetIdentifier())
        {*/
            window->HandleEvent(event);
            return;
        //}
    }
}

WindowObject* WindowSubsystem::GetWindowById(const StringId& Id)
{
    for(WindowObject* windowObject: windowObjects)
    {
        if(windowObject->GetId() == Id)
        {
            return windowObject;
        }
    }

    return nullptr;
}

WindowObject* WindowSubsystem::GetCurrentWindow() const
{
    return currentWidnow;
}

void WindowSubsystem::CreateScreenMesh()
{
    Array<MeshBuffer<float>> buffers;

    MeshBuffer<float> positions;
    positions.Type = BufferType::VEC2;
    positions.Array = new float[8]{ -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f };
    positions.Length = 8;
    buffers.Add(positions);

    MeshBuffer<float> texCoords;
    texCoords.Type = BufferType::VEC2;
    texCoords.Array = new float[8]{ 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
    texCoords.Length = 8;
    buffers.Add(texCoords);

    MeshBuffer<int> indicies;
    indicies.Type = BufferType::SINGLE;
    indicies.Array = new int[6]{ 0, 1, 2, 1, 3, 2 };
    indicies.Length = 6;
    screenMesh = new Mesh(buffers, indicies);
}

const char* vertexScreenShaderContent = "#version 450\n"
    "layout (location = 0) in vec2 position;\n"
    "layout (location = 1) in vec2 texCoords;\n"
    "out vec2 TexCoords;\n"
    "void main()\n"
    "{\n"
    "    TexCoords = texCoords;\n"
    "    gl_Position = vec4(position, 0.0, 1.0);\n"
    "}\n\0";

const char* fragmentScreenShaderContent = "#version 450\n"
    "layout (location=0) out vec4 o_Color;\n"
    "uniform sampler2D framebuffer;\n"
    "in vec2 TexCoords;\n"
    "void main()\n"
    "{\n"
    "	o_Color = texture(framebuffer, TexCoords);\n"
    "}\n\0";

void WindowSubsystem::CreateScreenShader()
{
    uint32_t glId;
    Map<StringId, uint32_t> uniforms;
    Map<StringId, uint32_t> textures;

    glId = glCreateProgram();

    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexScreenShaderContent, nullptr);
    glCompileShader(vertexShader);
    GlShaderCheckError(vertexShader, GL_COMPILE_STATUS);
    glAttachShader(glId, vertexShader);
    GlProgramCheckError(glId, GL_ATTACHED_SHADERS);

    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentScreenShaderContent, nullptr);
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

    screenShader = new Shader(glId, uniforms, textures);
}

class Mesh* WindowSubsystem::GetScreenMesh()
{
    return screenMesh;
}

class Shader* WindowSubsystem::GetScreenShader()
{
    return screenShader;
}