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
HeroInt2 *pos;
float speed = 100.0f;
HeroInt2 size = {64, 64};
float angle = 0.0f;
float rotSpeed = 30.0f;

void update(void* ptr)
{
    double deltaTime = heroCoreGetDeltaTime(core);
    int fps = (int)(1.0/deltaTime);
    printf("%d\n", fps);

    angle += rotSpeed * deltaTime;

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    heroSpriteBatchBegin(spriteBatch);

    for(int i =0 ; i < Num; i++)
    {
        int img = i%2;
        HeroInt4 rect = {0, 0, 32, 256};
        heroSpriteBatchDrawTextureEx(spriteBatch, texture[img], pos[i], size, rect, heroMathDeg2rad(angle));
    }

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

    pos = (HeroInt2*)malloc(Num*sizeof(HeroInt2));
    for(int i =0 ; i < Num; i++)
    {
        pos[i] = (HeroInt2){random(640 - size.x, 0), random(480 - size.y,0)};
    }

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