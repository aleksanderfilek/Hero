#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#include"Hero/H_headers.h"

typedef void (*func)(void* data);

typedef struct
{
    void* data;
    func update;
    func destroy;
} Module;

typedef struct
{
    char** names;
    Module* module;
    uint32_t capacity;
    uint32_t length;
} ModuleSet;


typedef struct 
{
    // status
    bool quit;

    // time
    double time_deleta;

    ModuleSet modules;
} HeroCore;

static void DeleteModule(HeroCore* core, Module* module, uint32_t index);

HeroCore* heroCoreInit()
{
    srand(time(NULL));

    // Initialize SDL
    if(SDL_Init(SDL_INIT_TIMER) < 0){
        printf("SDL could not initialize! SDL Error: %s\n",SDL_GetError());
        return NULL;
    }

    HeroCore* core = (HeroCore*)malloc(sizeof(HeroCore));
    memset(core, 0, sizeof(HeroCore));
    core->quit = false;

    return core;
}

void heroCoreStart(HeroCore* core)
{
    uint32_t timer;

    while (core->quit == false)
    {
        timer = SDL_GetTicks();

        for(int i = 0; i < core->modules.length && core->quit == false; i++)
        {
            Module* module = &core->modules.module[i];
            if(module->update == NULL)
            {
                continue;
            }
            module->update(module->data);
        }

        core->time_deleta = (double)(SDL_GetTicks() - timer )/1000.0f;
    }

    ModuleSet* modules = &core->modules;

    for(int i = modules->length-1; i >= 0; i--)
    {
        Module* module = &modules->module[i];
        DeleteModule(core, module, i);
    }

    free(modules->module);
    free(modules->names);

    SDL_Quit();
}

void heroCoreClose(HeroCore* core)
{
    core->quit = true;
}

double heroCoreGetDeltaTime(const HeroCore* core)
{
    return core->time_deleta;
}

void heroCoreModuleSetCapacity(HeroCore* core, uint32_t new_capacity)
{
    ModuleSet* modules = &core->modules;

    modules->capacity = new_capacity;
    modules->module = (Module*)realloc(modules->module, new_capacity * sizeof(Module));
    modules->names = (char**)realloc(modules->names, new_capacity * sizeof(char*));
}

void heroCoreModuleAdd(HeroCore* core, char* name, void* data, 
                        void (*update)(void* data), void (*destroy)(void* ptr))
{
    ModuleSet* modules = &core->modules;
    Module* module = NULL;
    // check already allocated memory
    for(int i = 0; i < modules->length; i++)
    {
        module = &modules->module[i];

        if(modules->names != NULL)
        {
            continue;
        }

        module->data = data;
        module->update = update;
        module->destroy = destroy;

        modules->names[i] = name;
        return;
    }

    if(modules->length == modules->capacity)
    {
        heroCoreModuleSetCapacity(core, modules->capacity + 1);
    }

    module = &modules->module[modules->length];
    module->data = data;
    module->update = update;
    module->destroy = destroy;
    modules->names[modules->length] = name;
    modules->length++;
}

void* heroCoreModuleGet(HeroCore* core, const char* name)
{
    ModuleSet* modules = &core->modules;

    for(int i = 0; i < modules->length; i++)
    {
        if(strcmp(name,modules->names[i]) != 0)
        {
            continue;
        }

        return modules->module[i].data;
    }

    return NULL;
}

void heroCoreModuleRemove(HeroCore* core, const char* name)
{
    ModuleSet* modules = &core->modules;

    for(int i = 0; i < modules->length; i++)
    {


        if(strcmp(name,modules->names[i]) != 0)
        {
            continue;
        }

        Module* module = &modules->module[i];

        DeleteModule(core, module, i);

        return;
    }
}

static void DeleteModule(HeroCore* core, Module* module, uint32_t index)
{
    if(module->data == NULL)
    {
        goto skipData;
    }

    if(module->destroy == NULL)
    {
        free(module->data);
    }
    else
    {
        module->destroy(module->data);
    }

skipData:

    core->modules.names[index] = NULL;
    memset(module, 0, sizeof(Module));
}
