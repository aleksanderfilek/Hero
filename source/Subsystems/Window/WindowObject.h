#pragma once

#include "../../Definitions.h"
#include "WindowSubsystem.h"
#include "../../ThirdParty/SDL2/SDL.h"
#include "../../ThirdParty/GL/Gl.h"
#include "../../ThirdParty/SDL2/SDL_opengl.h"

class HERO_API WindowObject
{
private:
    WindowConfiguration configuration;
    WindowSubsystem* windowSubsystem;

    uint32_t windowId = 0;
	SDL_Window* sdlWindow = nullptr;
	SDL_Renderer* sdlRenderer = nullptr;
	SDL_GLContext glContext;

public:
    WindowObject(const WindowConfiguration& WindowConfig, WindowSubsystem* WindowSubsystem);
    ~WindowObject();

    void Close();

    WindowConfiguration& GetConfiguration() { return configuration; }
};