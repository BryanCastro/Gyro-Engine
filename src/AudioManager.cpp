#include <iostream>
#include "AudioManager.h";

Mix_Chunk* AudioManager::LoadSound(const char* fileName){
    Mix_Chunk *sound = Mix_LoadWAV(fileName);
    if(sound==nullptr){
        std::cerr<<"Failed to load sound: "<<fileName<<std::endl;
    }
    return sound;
}

void AudioManager::PlaySound(Mix_Chunk *sound){
    Mix_PlayChannel(-1, sound, 0);
}