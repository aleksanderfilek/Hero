#include "WindowObject.h"
#include "WindowSubsystem.h"
#include "../../ThirdParty/SDL2/SDL.h"
#include "../../ThirdParty/GL/Gl.h"
#include "../../ThirdParty/SDL2/SDL_opengl.h"
#include "../../Graphics/RenderTarget.h"
#include "../Resource/ResourceSubsystem.h"
#include "../../Resources/Mesh.h"
#include "../../Resources/Shader.h"

WindowObject::WindowObject(const StringId& Id, const WindowConfiguration& WindowConfig, WindowSubsystem* WindowSubsystem)
    : id(Id), configuration(WindowConfig), windowSubsystem(WindowSubsystem)
{
    sdlWindow = SDL_CreateWindow(*configuration.Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, configuration.Size.X, configuration.Size.Y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (!sdlWindow) {
        //std::cout << "[" << getSidString(id) << "] Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    windowId = SDL_GetWindowID(sdlWindow);

    glContext = SDL_GL_CreateContext(sdlWindow);

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer)
    {
        //std::cout << "[" << getSidString(id) << "] Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;

    glewInit();

    glViewport(0, 0, configuration.Size.X, configuration.Size.Y);

    ResizeRenderTarget(configuration.Size);
}

WindowObject::~WindowObject()
{
    delete combinedRenderTarget;
    for(WindowRenderTarget& windowRenderTarget: renderTargets)
    {
        delete windowRenderTarget.RenderTarget;
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
}

void WindowObject::Close()
{
    windowSubsystem->CloseWindow(this);
}

void WindowObject::HandleEvent(SDL_Event* Event)
{
    switch (Event->window.event)
    {
    case SDL_WINDOWEVENT_SHOWN:
        shown = true;
        OnWindowEventShown.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_HIDDEN:
        shown = false;
        OnWindowEventHidden.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_EXPOSED:
        OnWindowEventExposed.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_MOVED:
        OnWindowEventMoved.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_RESIZED: {
        configuration.Size = { Event->window.data1, Event->window.data2 };
        glViewport(0, 0, configuration.Size.X, configuration.Size.Y);
        OnWindowEventResized.Broadcast(this, configuration.Size);
        ResizeRenderTarget(configuration.Size);
    } break;
    case SDL_WINDOWEVENT_SIZE_CHANGED: {
        configuration.Size = { Event->window.data1, Event->window.data2 };
        glViewport(0, 0, configuration.Size.X, configuration.Size.Y);
        OnWindowEventSizeChanged.Broadcast(this, configuration.Size);
    } break;
    case SDL_WINDOWEVENT_MINIMIZED:
        minimized = true;
        OnWindowEventMinimized.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_MAXIMIZED:
        minimized = false;
        OnWindowEventMaximized.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_RESTORED:
        minimized = false;
        OnWindowEventRestored.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_ENTER:
        mouseHover = true;
        OnWindowEventEnter.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_LEAVE:
        mouseHover = false;
        OnWindowEventLeave.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
        focused = true;
        OnWindowEventFocusGained.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
        focused = false;
        OnWindowEventFocusLost.Broadcast(this);
        break;
    case SDL_WINDOWEVENT_CLOSE:
        OnWindowEventClose.Broadcast(this);
        Close();
        break;
    }
    OnWindowEventCustom.Broadcast(Event);
}

void WindowObject::ResizeRenderTarget(const Int2& Size)
{
    if(combinedRenderTarget)
    {
        delete combinedRenderTarget;
        combinedRenderTarget = nullptr;
    }

    combinedRenderTarget = new RenderTarget(Size, false);
    for(WindowRenderTarget& windowRenderTarget: renderTargets)
    {
        delete windowRenderTarget.RenderTarget;
        windowRenderTarget.RenderTarget = new RenderTarget(Size, false);
    }
}

static void CreateWindowRenderTargetRaw(const StringId& Id, const Int2& Size, WindowRenderTarget& WindowRenderTarget)
{
    WindowRenderTarget.Id = Id;
    WindowRenderTarget.RenderTarget = new RenderTarget(Size, false);
}

WindowRenderTarget* WindowObject::CreateWindowRenderTarget(const StringId& Id)
{
    WindowRenderTarget windowRenderTarget;
    CreateWindowRenderTargetRaw(Id, configuration.Size, windowRenderTarget);

    renderTargets.Add(windowRenderTarget);
    return &renderTargets[renderTargets.Length() - 1];
}

WindowRenderTarget* WindowObject::GetWindowRenderTarget(const StringId& Id)
{
    for(int i = 0; i < renderTargets.Length(); i++)
    {
        if(renderTargets[i].Id == Id)
        {
            return &renderTargets[i];
        }
    }

    return CreateWindowRenderTarget(Id);
}

void WindowObject::RemoveWindowRenderTarget(const StringId& Id)
{
    int indexToRemove = renderTargets.Length();
    for(int i = 0; i < renderTargets.Length(); i++)
    {
        if(renderTargets[i].Id == Id)
        {
            indexToRemove = i;
        }
    }

    if(indexToRemove == renderTargets.Length())
    {
        return;
    }

    WindowRenderTarget& windowRenderTarget = renderTargets[indexToRemove];
    delete windowRenderTarget.RenderTarget;
    renderTargets.RemoveAt(indexToRemove);
}

void WindowObject::SetWindowRenderTargetOrder(const Array<StringId>& OrderIds)
{
    Array<WindowRenderTarget> orderedRenderTargets;
    for(const StringId& id: OrderIds)
    {
        const WindowRenderTarget* foundRenderTarget = nullptr;
        for(const WindowRenderTarget& windowRenderTarget: renderTargets)
        {
            if(windowRenderTarget.Id == id)
            {
                foundRenderTarget = &windowRenderTarget;
                break;
            }
        }

        if(foundRenderTarget)
        {
            orderedRenderTargets.Add(*foundRenderTarget);
        }
        else
        {
            WindowRenderTarget windowRenderTarget;
            CreateWindowRenderTargetRaw(id, configuration.Size, windowRenderTarget);
            orderedRenderTargets.Add(windowRenderTarget);
        }
    }

    renderTargets = orderedRenderTargets;
}

void WindowObject::Render()
{
    // set current context
    SDL_GL_MakeCurrent(sdlWindow, glContext);

    // render buffers to combined buffer
    combinedRenderTarget->BindBuffers();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // clear combined buffer
    glClearColor(
        (float)configuration.BackgroundColor.R/255.0f,
        (float)configuration.BackgroundColor.G/255.0f,
        (float)configuration.BackgroundColor.B/255.0f,
        1.0f
    );
    combinedRenderTarget->Clear();

    windowSubsystem->GetScreenShader()->Bind();
    for(WindowRenderTarget& windowRenderTarget: renderTargets)
    {
        windowRenderTarget.RenderTarget->BindTexture();
        windowSubsystem->GetScreenMesh()->Draw();
    }
    glDisable(GL_BLEND);
    combinedRenderTarget->UnbindBuffers();
    
    // blit combined buffer to default buffer
    combinedRenderTarget->BlitToBuffer(0, configuration.Size);
    SDL_GL_SwapWindow(sdlWindow);

}