#include<stdio.h>
#include<stdlib.h>

#include"Hero.h"

HeroCore* core;

void closeGame(void* data)
{
    heroCoreClose(core);
}

HeroInput* input;

void update(void* ptr)
{
    static int counter = 0;
    if(heroInputKeyPressed(input, HERO_KEYCODE_A))
    {
        printf("%d = A\n", counter);
        counter++;
    }

    if(heroInputKeyDown(input, HERO_KEYCODE_D))
    {
        printf("%d = D\n", counter);
        counter++;
    }

    if(heroInputKeyUp(input, HERO_KEYCODE_W))
    {
        printf("%d = W\n", counter);
        counter++;
    }
}

int main(int argc, char *argv[])
{
    core = heroCoreInit();

    {
        void* win1 = heroWindowInit("window 1", 640, 480, 0);
        heroWindowSetEvent((HeroWindow*)win1, HERO_WINDOW_CLOSE, closeGame);
        heroCoreModuleAdd(core, "window1", win1, NULL, heroWindowDestroy);
        input = heroInputInit();
        heroCoreModuleAdd(core, "input", input, heroInputUpdate, heroInputDestroy);
        void* ptr = heroEventInit();
        heroEventAddWindow(ptr, (HeroWindow*)win1);
        heroCoreModuleAdd(core, "event", ptr, heroEventUpdate, heroEventDestroy);
        heroCoreModuleAdd(core, "update", NULL, update, NULL);
    }

    heroCoreStart(core);

    return 0;
}