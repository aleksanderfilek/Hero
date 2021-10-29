#ifndef HERO_AUDIO_H_
#define HERO_AUDIO_H_

#include<stdbool.h>

#include"H_audiotypes.h"

typedef void* HeroAudio;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroAudio* heroAudioInit(int frequency, HeroChannelType channelType, uint16_t format, int chunksize, HeroAudioFormat fileFormat);
extern void heroAudioDestroy(void* ptr);

extern HeroMusic* heroAudioMusicLoad(const char* path);
extern void heroAudioMusicUnload(HeroMusic* music);
extern void heroAudioMusicPlay(HeroMusic* music, bool loop);
extern void heroAudioMusicStop();
extern void heroAudioMusicResume();
extern void heroAudioMusicPause();
extern bool heroAudioMusicIsPlaying();
extern bool heroAudioMusicIsPaused();
extern void heroAudioMusicSetVolume(int volume);

extern HeroSound* heroAudioSoundLoad(const char* path);
extern void heroAudioSoundUnload(HeroSound* sound);
extern void heroAudioSoundPlay(HeroSound* sound, bool loop);
extern void heroAudioSoundSetVolume(int volume);


#ifdef __cplusplus
}
#endif

#endif