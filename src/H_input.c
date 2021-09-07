#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>

#include<SDL2/SDL.h>

#include"H_mouse.h"
#include"H_keycode.h"

typedef struct
{
    int keyboard_state_number;
    const uint8_t *current_keyboard_state;
    uint8_t *previous_keyboard_state;
    int32_t current_mouse_state, previous_mouse_state;
    int mouse_position_X;
    int mouse_position_Y;
} H_Input;

H_Input* H_input_init()
{
    H_Input* input = (H_Input*)malloc(sizeof(H_Input));
    memset(input, 0 , sizeof(H_Input));

    input->current_keyboard_state = SDL_GetKeyboardState(&input->keyboard_state_number);
    input->previous_keyboard_state = (uint8_t*)malloc(input->keyboard_state_number * sizeof(uint8_t));
    memset(input->previous_keyboard_state, 0, input->keyboard_state_number * sizeof(uint8_t));

    return input;
}

void H_input_update(void* input)
{
    H_Input* _input = (H_Input*)input;

    //update mouse
    _input->previous_mouse_state = _input->current_mouse_state;
    _input->current_mouse_state = SDL_GetMouseState(&_input->mouse_position_X, &_input->mouse_position_Y);
    //update keyboard
    SDL_memcpy(_input->previous_keyboard_state, _input->current_keyboard_state, _input->keyboard_state_number * sizeof(uint8_t));
}

void H_input_destroy(void* ptr)
{
    free(((H_Input*)ptr)->previous_keyboard_state);
}

bool H_key_pressed(const H_Input* input, H_KeyCode key)
{
    return input->current_keyboard_state[key] && input->previous_keyboard_state[key];
}

bool H_key_down(const H_Input* input, H_KeyCode key)
{
    return input->current_keyboard_state[key] && !input->previous_keyboard_state[key];
}

bool H_key_up(const H_Input* input, H_KeyCode key)
{
    return !input->current_keyboard_state[key] && input->previous_keyboard_state[key];
}

bool H_mouse_buttonp_pressed(const H_Input* input, H_Mouse_Button button)
{
    return input->current_mouse_state&SDL_BUTTON(button) && input->previous_mouse_state&SDL_BUTTON(button);
}

bool H_mouse_buttonp_down(const H_Input* input, H_Mouse_Button button)
{
    return input->current_mouse_state&SDL_BUTTON(button) && !input->previous_mouse_state&SDL_BUTTON(button);
}

bool H_mouse_buttonp_up(const H_Input* input, H_Mouse_Button button)
{
    return !input->current_mouse_state&SDL_BUTTON(button) && input->previous_mouse_state&SDL_BUTTON(button);
}

void H_get_mouse_position(const H_Input* input, int *x, int *y)
{
    if(x != NULL) *x = input->mouse_position_X;
    if(y != NULL) *y = input->mouse_position_Y;
}

void H_set_mouse_position(H_Input* input, int x, int y)
{
    input->mouse_position_X = x;
    input->mouse_position_Y = y;
}
