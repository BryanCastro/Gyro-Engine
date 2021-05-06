#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL2/SDL_mixer.h>

class AudioManager{
    public:
        static Mix_Chunk* LoadSound(const char* fileName);
        static Mix_Music* LoadMusic(const char* fileName);
        static void PlaySound(Mix_Chunk *sound);
        static void PlayMusic(Mix_Music *music);
        
};

#endif