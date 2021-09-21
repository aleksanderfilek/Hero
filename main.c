#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"Hero.h"

HeroCore* core;


void closeGame(void* data)
{
    heroCoreClose(core);
}

#define Num 100000

HeroInput* input;
HeroShader* shader;
HeroSpriteBatch* spriteBatch;
HeroTexture* texture[2];
SDL_Window* window;

void update(void* ptr)
{
    double deltaTime = heroCoreGetDeltaTime(core);
    int fps = (int)(1.0/deltaTime);
    printf("%d\n", fps);

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    heroSpriteBatchBegin(spriteBatch);

    heroSpriteBatchEnd(spriteBatch);

    SDL_GL_SwapWindow(window);
}

int random(int max, int min)
{
    return rand()%max + min;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    core = heroCoreInit();

    {
        void* win1 = heroWindowInit("window 1", 640, 480, 0);
        window = heroWindowGetSdlWindow(win1);
        heroWindowSetEvent((HeroWindow*)win1, HERO_WINDOW_CLOSE, closeGame);
        heroCoreModuleAdd(core, "window1", win1, NULL, heroWindowDestroy);

        input = heroInputInit();
        heroCoreModuleAdd(core, "input", input, heroInputUpdate, heroInputDestroy);

        void* ptr = heroEventInit();
        heroEventAddWindow(ptr, (HeroWindow*)win1);
        heroCoreModuleAdd(core, "event", ptr, heroEventUpdate, heroEventDestroy);
        
        heroCoreModuleAdd(core, "update", NULL, update, NULL);

        texture[0] = heroTextureLoad("assets/image.png", HERO_TEXTUREFLAG_NEAREST | HERO_TEXTUREFLAG_MIPMAP);
        texture[1] = heroTextureLoad("assets/red.png", HERO_TEXTUREFLAG_NEAREST | HERO_TEXTUREFLAG_MIPMAP);
        shader = heroShaderLoad("assets/shader.vert", "assets/shader.frag");
        spriteBatch = heroSpriteBatchInit(10000, 10, shader);
    }

    heroCoreStart(core);

    heroSpriteBatchDestroy(spriteBatch);
    heroShaderUnload(shader);
    heroTextureUnload(texture[0]);
    heroTextureUnload(texture[1]);

    return 0;
}