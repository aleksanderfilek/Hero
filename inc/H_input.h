#ifndef HERO_INPUT_H_
#define HERO_INPUT_H_

#include<stdbool.h>

#include"H_mouse.h"
#include"H_keycode.h"

typedef void* H_Input;

#ifdef __cplusplus
extern "C" {
#endif

extern H_Input* H_input_init();
extern void H_input_update(void* input);
extern void H_input_destroy(void* ptr);

extern bool H_key_pressed(const H_Input* input, H_KeyCode key);
extern bool H_key_down(const H_Input* input, H_KeyCode key);
extern bool H_key_up(const H_Input* input, H_KeyCode key);

extern bool H_mouse_buttonp_pressed(const H_Input* input, H_Mouse_Button button);
extern bool H_mouse_buttonp_down(const H_Input* input, H_Mouse_Button button);
extern bool H_mouse_buttonp_up(const H_Input* input, H_Mouse_Button button);

extern void H_get_mouse_position(const H_Input* input, int *x, int *y);
extern void H_set_mouse_position(H_Input* input, int x, int y);

#ifdef __cplusplus
}
#endif

#endif