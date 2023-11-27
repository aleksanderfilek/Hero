#include"Input.hpp"
#include "../Core/Core.hpp"
#include "Window.hpp"

#include<iostream>

namespace Hero
{
namespace System
{

HERO Input::Input(const Sid& sid) : ISystem(sid)
{
    priority = 253;

    this->current_keyboard_state = SDL_GetKeyboardState(&this->keyboard_state_number);
    this->previous_keyboard_state = new std::uint8_t[this->keyboard_state_number];
}

HERO Input::~Input()
{
    delete[] this->previous_keyboard_state;
}

HERO void Input::init()
{
    ISystem::init();
}

HERO void Input::update()
{
    //update mouse
    previous_mouse_state = current_mouse_state;
    previousMousePositionX = mouse_position_X;
    previousMousePositionY = mouse_position_Y;
    if(relativeMode == false)
    {
        current_mouse_state = SDL_GetMouseState(&mouse_position_X, &mouse_position_Y);
    }
    else
    {
        current_mouse_state = SDL_GetRelativeMouseState(&mouse_position_X, &mouse_position_Y);
    }
    //update keyboard
    SDL_memcpy(this->previous_keyboard_state, current_keyboard_state, keyboard_state_number * sizeof(std::uint8_t));
}

HERO void Input::close()
{
    ISystem::close();
}

HERO Int2 Input::getMousePosition()
{
    if(!relativeMode)
        return {mouse_position_X , mouse_position_Y};

    Int2 size = Core::getSystem<System::Window>(SID("Window"))->getSize();
    return { size.x / 2, size.y / 2};
}

HERO void Input::setMousePosition(Int2 position)
{
    mouse_position_X = position.x;
    mouse_position_Y = position.y; 
}

HERO uint8_t Input::getMouseState(Mouse button)
{
    uint8_t state = 0;
    if(mouseButtonDown(button)) state |= 1<<0;
    if(mouseButtonPressed(button)) state |= 1<<1;
    if(mouseButtonUp(button)) state |= 1<<2;

    return state;
}

HERO Int2 Input::getMouseDeltaPosition()
{
    Int2 result;
    if(relativeMode == false)
    {
        result = {
            mouse_position_X - previousMousePositionX,
            mouse_position_Y - previousMousePositionY
        };
    }
    else
    {
        result = { mouse_position_X , mouse_position_Y};
    }
    return result;
}

HERO void Input::setRelativeMode(bool enable)
{
    relativeMode = enable;
    SDL_SetRelativeMouseMode((enable == true)? SDL_TRUE : SDL_FALSE);
    mouse_position_X = 0;
    mouse_position_Y = 0;
}

}
}