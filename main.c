#include<stdio.h>
#include<stdlib.h>

#include"Hero.h"

H_Core* core;

void closeGame(void* data)
{
    H_Core_close(core);
}

H_Input* input;

void update(void* ptr)
{
    static int counter = 0;
    if(H_key_pressed(input, H_KEYCODE_A))
    {
        printf("%d = A\n", counter);
        counter++;
    }

    if(H_key_down(input, H_KEYCODE_D))
    {
        printf("%d = D\n", counter);
        counter++;
    }

    if(H_key_up(input, H_KEYCODE_W))
    {
        printf("%d = W\n", counter);
        counter++;
    }
}

int main(int argc, char *argv[])
{
    //H_Texture* texture = H_LoadTexture("image.png", H_TEXTUREFLAG_LINEAR);

    core = H_Core_init();

    {
        void* win1 = H_Window_init("window 1", 640, 480, 0);
        H_Window_set_event((H_Window*)win1, H_WINDOW_CLOSE, closeGame);
        H_Core_Module_add(core, "window1", win1, NULL, H_Window_destroy);
        input = H_input_init();
        H_Core_Module_add(core, "input", input, H_input_update, H_input_destroy);
        void* ptr = H_Event_init();
        H_Event_add_window(ptr, (H_Window*)win1);
        H_Core_Module_add(core, "event", ptr, H_Event_update, H_Event_destroy);
        H_Core_Module_add(core, "update", NULL, update, NULL);
    }

    //H_UnloadTexture(texture);

    H_Core_start(core);

    return 0;
}