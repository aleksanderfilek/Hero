#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>

#include<SDL2/SDL.h>

#include"H_mouse.h"
#include"H_keycode.h"

typedef struct
{
    int keyboardStateNumber;
    const uint8_t *currentKeyboardState;
    uint8_t *previousKeyboardState;
    int32_t currentMouseState, previousMouseState;
    int mousePositionX;
    int mousePositionY;
} HeroInput;

HeroInput* heroInputInit()
{
    HeroInput* input = (HeroInput*)malloc(sizeof(HeroInput));
    memset(input, 0 , sizeof(HeroInput));

    input->currentKeyboardState = SDL_GetKeyboardState(&input->keyboardStateNumber);
    input->previousKeyboardState = (uint8_t*)malloc(input->keyboardStateNumber * sizeof(uint8_t));
    memset(input->previousKeyboardState, 0, input->keyboardStateNumber * sizeof(uint8_t));

    return input;
}

void heroInputUpdate(void* input)
{
    HeroInput* _input = (HeroInput*)input;

    //update mouse
    _input->previousMouseState = _input->currentMouseState;
    _input->currentMouseState = SDL_GetMouseState(&_input->mousePositionX, &_input->mousePositionY);
    //update keyboard
    SDL_memcpy(_input->previousKeyboardState, _input->currentKeyboardState, _input->keyboardStateNumber * sizeof(uint8_t));
}

void heroInputDestroy(void* ptr)
{
    free(((HeroInput*)ptr)->previousKeyboardState);
}

bool heroInputKeyPressed(const HeroInput* input, HeroKeyCode key)
{
    return input->currentKeyboardState[key] && input->previousKeyboardState[key];
}

bool heroInputKeyDown(const HeroInput* input, HeroKeyCode key)
{
    return input->currentKeyboardState[key] && !input->previousKeyboardState[key];
}

bool heroInputKeyUp(const HeroInput* input, HeroKeyCode key)
{
    return !input->currentKeyboardState[key] && input->previousKeyboardState[key];
}

bool heroInputMouseButtonPressed(const HeroInput* input, HeroMouseButton button)
{
    return input->currentMouseState&SDL_BUTTON(button) && input->previousMouseState&SDL_BUTTON(button);
}

bool heroInputMouseButtonDown(const HeroInput* input, HeroMouseButton button)
{
    return input->currentMouseState&SDL_BUTTON(button) && !input->previousMouseState&SDL_BUTTON(button);
}

bool heroInputMouseButtonUp(const HeroInput* input, HeroMouseButton button)
{
    return !input->currentMouseState&SDL_BUTTON(button) && input->previousMouseState&SDL_BUTTON(button);
}

void heroInputGetMousePosition(const HeroInput* input, int *x, int *y)
{
    if(x != NULL) *x = input->mousePositionX;
    if(y != NULL) *y = input->mousePositionY;
}

void heroInputSetMousePosition(HeroInput* input, int x, int y)
{
    input->mousePositionX = x;
    input->mousePositionY = y;
}
