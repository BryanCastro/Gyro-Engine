#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include "../Component.h"
#include "../Game.h"
#include "../AudioManager.h"
#include <SDL2/SDL_mixer.h>

class SoundComponent: public Component{
    private:
        Mix_Chunk* sound;
    public:
        SoundComponent(std::string soundId){
            sound = Game::assetManager->GetSound(soundId);
        }

        void Initialize() override{
            AudioManager::PlaySound(sound);
        }
};

#endif