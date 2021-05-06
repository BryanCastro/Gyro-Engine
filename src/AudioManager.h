#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL2/SDL_mixer.h>

class AudioManager{
    public:
        static Mix_Chunk* LoadSound(const char* fileName);
        static void PlaySound(Mix_Chunk *sound);

};

#endif