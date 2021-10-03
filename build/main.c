#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"Hero.h"

HeroCore* core;

void closeGame(void* data)
{
    heroCoreClose(core);
}

int main(int argc, char *argv[])
{
    core = heroCoreInit();

    {
        void* window = heroWindowInit("window", 640, 480, 0);
        heroWindowSetEvent((HeroWindow*)window, HERO_WINDOW_CLOSE, closeGame);
        heroCoreModuleAdd(core, "window", window, NULL, heroWindowDestroy);

        void* audio = heroAudioInit(HERO_AUDIO_FREQUENCY_22050, HERO_AUDIO_CHANNEL_MONO, MIX_DEFAULT_FORMAT, 2048, HERO_AUDIO_FORMAT_MP3);
        heroCoreModuleAdd(core, "audio", audio, NULL, heroAudioDestroy);
        HeroMusic* music = heroAudioMusicLoad("assets/music.mp3");
        heroAudioMusicPlay(music, false);
        heroAudioMusicSetVolume(1);

        void* input = heroInputInit();
        heroCoreModuleAdd(core, "input", input, heroInputUpdate, heroInputDestroy);

        void* event = heroEventInit();
        heroEventAddWindow(event, (HeroWindow*)window);
        heroCoreModuleAdd(core, "event", event, heroEventUpdate, heroEventDestroy);
    }

    heroCoreStart(core);

    return 0;
}