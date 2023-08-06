#include "WindowSubsystem.h"

WindowSubsystem WindowSubsystem::instance = nullptr;

WindowSubsystem::WindowSubsystem()
{

}

WindowSubsystem::~WindowSubsystem()
{
    for(WindowObject* window: windowObjects)
    {
        delete[] window;
    }
}

void WindowSubsystem::CreateWindow(const WindowConfiguration& WindowConfig)
{

}

void WindowSubsystem::CloseWindow(class WindowObject* Window)
{

}