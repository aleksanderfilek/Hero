#ifndef HERO_AUDIOTYPES_H_
#define HERO_AUDIOTYPES_H_

#include"H_headers.h"

typedef Mix_Music HeroMusic;
typedef Mix_Chunk HeroSound;

#define HERO_AUDIO_MAX_VOLUME 128

#define HERO_AUDIO_FREQUENCY_22050 22050
#define HERO_AUDIO_FREQUENCY_44100 44100

typedef enum
{
    HERO_AUDIO_CHANNEL_MONO = 1,
    HERO_AUDIO_CHANNEL_STEREO = 2
} HeroChannelType;

typedef enum
{
    HERO_AUDIO_FORMAT_WAV = 0,
    HERO_AUDIO_FORMAT_FLAC = 1,
    HERO_AUDIO_FORMAT_MOD = 2,
    HERO_AUDIO_FORMAT_MP3 = 8,
    HERO_AUDIO_FORMAT_OGG = 16
} HeroAudioFormat;

#endif