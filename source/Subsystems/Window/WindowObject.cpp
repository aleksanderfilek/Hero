#include "WindowObject.h"

WindowObject::WindowObject(const WindowConfiguration& WindowConfig, WindowSubsystem* WindowSubsystem)
    : configuration(WindowConfig), windowSubsystem(WindowSubsystem)
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

    glViewport(0, 0, configuration.Size.X, configuration.Size.Y);
}

WindowObject::~WindowObject()
{

}

void WindowObject::Close()
{
    windowSubsystem->CloseWindow(this);
}