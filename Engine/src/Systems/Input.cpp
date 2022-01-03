#include"Input.hpp"

namespace Hero
{
namespace System
{

Input::Input(const Sid& sid) : ISystem(sid)
{
    this->current_keyboard_state = SDL_GetKeyboardState(&this->keyboard_state_number);
    this->previous_keyboard_state = new std::uint8_t[this->keyboard_state_number];
}

Input::~Input()
{
    delete this->previous_keyboard_state;
}

void Input::init()
{
    ISystem::init();
}

void Input::update()
{
    //update mouse
    this->previous_mouse_state = this->current_mouse_state;
    this->current_mouse_state = SDL_GetMouseState(&this->mouse_position_X, &this->mouse_position_Y);
    //update keyboard
    SDL_memcpy(this->previous_keyboard_state, this->current_keyboard_state, this->keyboard_state_number * sizeof(std::uint8_t));
}

void Input::close()
{
    ISystem::close();
}

}
}