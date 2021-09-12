#include<stdio.h>
#include<stdlib.h>

#include"Hero.h"

HeroCore* core;


void closeGame(void* data)
{
    heroCoreClose(core);
}

HeroInput* input;
HeroShader* shader;
HeroSpriteBatch* spriteBatch;
HeroTexture* texture;
SDL_Window* window;
HeroInt2 pos = {0.0f, 0.0f};
float speed = 100.0f;

void update(void* ptr)
{
    double deltaTime = heroCoreGetDeltaTime(core);
    if(heroInputKeyPressed(input, HERO_KEYCODE_S))
    {
        pos.y += (int)(speed * deltaTime);
    }
    else if(heroInputKeyPressed(input, HERO_KEYCODE_W))
    {
        pos.y -= (int)(speed * deltaTime);
    }

    if(heroInputKeyPressed(input, HERO_KEYCODE_D))
    {
        pos.x += (int)(speed * deltaTime);
    }
    else if(heroInputKeyPressed(input, HERO_KEYCODE_A))
    {
        pos.x -= (int)(speed * deltaTime);
    }

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    heroSpriteBatchBegin(spriteBatch);

    HeroInt2 size = {400, 400};
    heroSpriteBatchDrawTexture(spriteBatch, texture, pos, size);

    heroSpriteBatchEnd(spriteBatch);

    SDL_GL_SwapWindow(window);
}

int main(int argc, char *argv[])
{
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

        texture = heroTextureLoad("assets/image.png", HERO_TEXTUREFLAG_NEAREST | HERO_TEXTUREFLAG_MIPMAP);
        shader = heroShaderLoad("assets/shader.vert", "assets/shader.frag");

        spriteBatch = heroSpriteBatchInit(1, 10, shader);
    }

    heroCoreStart(core);

    heroSpriteBatchDestroy(spriteBatch);
    heroShaderUnload(shader);
    heroTextureUnload(texture);

    return 0;
}