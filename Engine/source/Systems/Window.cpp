#include"Window.hpp"
#include"../Core/Debug.hpp"
#include"../ThirdParty/SDL2/SDL_ttf.h"

namespace Hero
{
namespace System
{

HERO Window::Window(const Sid& sid, const char *title, int width, int height, int sdlflags)
 : ISystem(sid)
{
    priority = 0;

    if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        std::cout<<"["<<sid.getName()<<"] SDL_Init: "<<SDL_GetError()<<std::endl;
        printf("Window: SDL_Init %s\n", SDL_GetError());
        exit(-1);
    }

    sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, sdlflags | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(!sdlWindow){
        std::cout<<"["<<sid.getName()<<"] Window could not be created! SDL Error: "<<SDL_GetError()<<std::endl;
        return;
    }

    id = SDL_GetWindowID(sdlWindow);
    
    renderer = SDL_CreateRenderer(sdlWindow, - 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
    {
        std::cout<<"["<<sid.getName()<<"] Renderer could not be created! SDL Error: "<<SDL_GetError()<<std::endl;
        return;
    }

    size = {width, height};
    fullScreen = false;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);

    glContext = SDL_GL_CreateContext(sdlWindow);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;

    glewInit();
    glCheckError();

    glViewport(0,0,width, height);

    glClearColor(1.0f,1.0f,1.0f,1.0f);

    if(TTF_Init() < 0)
    {
        std::cout<<"["<<sid.getName()<<"] SDL_ttf could not be initialize! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
        return;
    }
}

HERO Window::~Window()
{
    printMessage("Quiting TTF");
    TTF_Quit();
    printMessage("Deleting GL context");
    SDL_GL_DeleteContext(glContext);
    printMessage("Destroying SDL renderer");
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    printMessage("Destroying SDL window");
    SDL_DestroyWindow(sdlWindow);
    sdlWindow = nullptr;
}

HERO void Window::init()
{
    ISystem::init();
}

HERO void Window::update()
{
    if(renderFlag)
    {
        SDL_GL_SwapWindow(sdlWindow);
    }
}

HERO void Window::close()
{
    ISystem::close();
}

HERO void Window::apply()
{

}

HERO void Window::handleEvents(SDL_Event* event)
{
    if(event->type == SDL_WINDOWEVENT && event->window.windowID == id)
    {

    switch( event->window.event )
    {
        case SDL_WINDOWEVENT_SHOWN:
            shown = true;
            events[(int)WindowEventType::SHOWN].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            shown = false;
            events[(int)WindowEventType::HIDDEN].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            events[(int)WindowEventType::EXPOSED].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_MOVED:
            events[(int)WindowEventType::MOVED].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_RESIZED: {
            size = (Int2){ event->window.data1, event->window.data2 };
            void* args[2] = {
                (void*)&size.x,
                (void*)&size.y
            };
            glViewport(0,0,size.x, size.y);

            events[(int)WindowEventType::RESIZED].invoke(this, args, 2);
        } break;
        case SDL_WINDOWEVENT_SIZE_CHANGED: {
            size = (Int2){ event->window.data1, event->window.data2 };
            void* args[2] = {
                (void*)&size.x,
                (void*)&size.y
            };
            glViewport(0,0,size.x, size.y);

            events[(int)WindowEventType::SIZE_CHANGED].invoke(this, args, 2);
        } break;
        case SDL_WINDOWEVENT_MINIMIZED:
            minimized = true;
            events[(int)WindowEventType::MINIMIZED].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            minimized = false;
            events[(int)WindowEventType::MAXIMIZED].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            minimized = false;
            events[(int)WindowEventType::RESTORED].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_ENTER:
            mouseHover = true;
            events[(int)WindowEventType::ENTER].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            mouseHover = false;
            events[(int)WindowEventType::LEAVE].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            focused = true;
            events[(int)WindowEventType::FOCUS_GAINED].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            focused = false;
            events[(int)WindowEventType::FOCUS_LOST].invoke(this, nullptr, 0);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            events[(int)WindowEventType::CLOSE].invoke(this, nullptr, 0);
            break;
    }

    }
}

static uint8_t depthEnabled = 0;

HERO void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | (depthEnabled * GL_DEPTH_BUFFER_BIT));
}

HERO void Window::setDepthTest(bool turnOn)
{
    depthEnabled = (turnOn)?1:0;
    if(turnOn) 
        glEnable(GL_DEPTH_TEST);  
    else 
        glDisable(GL_DEPTH_TEST);
}

HERO bool Window::isDepthTest()
{
    return depthEnabled;
}

HERO void Window::SetDefaultFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, size.x, size.y);
}

}
}
