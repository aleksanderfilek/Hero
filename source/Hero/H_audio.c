#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

#include"Hero/H_headers.h"
#include"Hero/H_debug.h"
#include"Hero/H_audiotypes.h"

typedef struct
{
    
} HeroAudio;


HeroAudio* heroAudioInit(int frequency, HeroChannelType channelType, uint16_t format, int chunksize, HeroAudioFormat fileFormat)
{
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        printf("Audio: SDL_Init %s\n", SDL_GetError());
        exit(-1);
    }

    if(fileFormat > 0)
    {
        if(Mix_Init(fileFormat) < 0)
        {
            printf("Mix_Init: Failed to init required format: %s\n", Mix_GetError());
            exit(-1);
        }
    }

    if(Mix_OpenAudio(frequency, format, channelType, chunksize) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(-1);
    }

    HeroAudio* audio = (HeroAudio*)malloc(sizeof(HeroAudio));


    return audio;
}

void heroAudioDestroy(void* ptr)
{
    Mix_Quit();

    free(ptr);
}

HeroMusic* heroAudioMusicLoad(const char* path)
{
    HeroMusic* music = Mix_LoadMUS(path);
    DEBUG_CODE(
        if(music == NULL)
        {
            printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
            return NULL;
        }
    );
    return music;
}

void heroAudioMusicUnload(HeroMusic* music)
{
    Mix_FreeMusic(music);
}

void heroAudioMusicPlay(HeroMusic* music, bool loop)
{
    Mix_PlayMusic(music, (loop == true)? -1: 1);
}

void heroAudioMusicStop()
{
    Mix_HaltMusic();
}

void heroAudioMusicResume()
{
    Mix_ResumeMusic();
}

void heroAudioMusicPause()
{
    Mix_PauseMusic();
}

bool heroAudioMusicIsPlaying()
{
    return Mix_PlayingMusic() == 1;
}

bool heroAudioMusicIsPaused()
{
    return Mix_PausedMusic() == 0;
}

void heroAudioMusicSetVolume(int volume)
{
    Mix_VolumeMusic(volume);
}

HeroSound* heroAudioSoundLoad(const char* path)
{
    HeroSound* sound = Mix_LoadWAV(path);
    DEBUG_CODE(
        if(sound == NULL)
        {
            printf("Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError());
            return NULL;
        }
    );
    return sound;
}

void heroAudioSoundPlay(HeroSound* sound, bool loop)
{
    Mix_PlayChannel(-1, sound, 0);
}

void heroAudioSoundUnload(HeroSound* sound)
{
    Mix_FreeChunk(sound);
}
