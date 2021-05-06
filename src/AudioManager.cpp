#include <iostream>
#include "AudioManager.h";

Mix_Chunk* AudioManager::LoadSound(const char* fileName){
    Mix_Chunk *sound = Mix_LoadWAV(fileName);
    if(sound==NULL){
        std::cerr<<"Failed to load sound: "<<fileName<<std::endl;
    }
    return sound;
}

Mix_Music* AudioManager::LoadMusic(const char* fileName){
    Mix_Music *music = Mix_LoadMUS(fileName);
    if(music==NULL){
        std::cerr<<"Failed to load music: "<<fileName<<std::endl;
    }
    return music;
}

void AudioManager::PlaySound(Mix_Chunk *sound){
    Mix_PlayChannel(-1, sound, 0);
}

void AudioManager::PlayMusic(Mix_Music *music){
    //If no music playing
    if(Mix_PlayingMusic()==0){
        //play music
        Mix_PlayMusic(music, -1);
    }
}