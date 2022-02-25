#include"Input.hpp"

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

HERO void Input::getMousePosition(int *x,int *y)
{
    if(x != NULL) *x = mouse_position_X;
    if(y != NULL) *y = mouse_position_Y; 
}
HERO void Input::setMousePosition(int x, int y)
{
    mouse_position_X = x;
    mouse_position_Y = y; 
}

HERO uint8_t Input::getMouseState(Mouse button)
{
    uint8_t state = 0;
    if(mouseButtonDown(button)) state |= 1<<0;
    if(mouseButtonPressed(button)) state |= 1<<1;
    if(mouseButtonUp(button)) state |= 1<<2;

    return state;
}

HERO void Input::getMouseDeltaPosition(int& x, int& y)
{
    if(relativeMode == false)
    {
        x = mouse_position_X - previousMousePositionX;
        y = mouse_position_Y - previousMousePositionY;
    }
    else
    {
        x = mouse_position_X;
        y = mouse_position_Y;
    }
}

HERO void Input::setRelativeMode(bool enable)
{
    relativeMode = enable;
    SDL_SetRelativeMouseMode((enable == true)? SDL_TRUE : SDL_FALSE);
}

}
}