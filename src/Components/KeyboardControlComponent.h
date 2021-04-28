#pragma once

#include <string>
#include <sstream>
#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
//#include "../Components/TransformComponent.h"
//#include "../Components/SpriteComponent.h"


//MinGW has problems with to_string function, this namespace 'patch' fixes the issue
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


class KeyboardControlComponent: public Component{
    public:

        KeyboardControlComponent(){

        }

        KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey){
            this->upKey = GetSDLKeyStringCode(upKey);
            this->rightKey = GetSDLKeyStringCode(rightKey);
            this->leftKey = GetSDLKeyStringCode(leftKey);
            this->downKey = GetSDLKeyStringCode(downKey);
            this->shootKey = GetSDLKeyStringCode(shootKey);
        }

        std::string GetSDLKeyStringCode(std::string key){
            if(key.compare("up")==0) return "1073741906";
            if(key.compare("down")==0) return "1073741905";
            if(key.compare("left")==0) return "1073741904";
            if(key.compare("right")==0) return "1073741903";
            if(key.compare("space")==0) return "32";

            return patch::to_string(static_cast<int>(key[0]));
        }

        void Initialize() override{
            transform = owner->GetComponent<TransformComponent>();
            sprite = owner->GetComponent<SpriteComponent>();
        }

        void Update(float deltaTime) override{
            if(Game::event.type==SDL_KEYDOWN){
                std::string keyCode = patch::to_string(Game::event.key.keysym.sym);
                if(keyCode.compare(upKey)==0){
                    transform->velocity.y = -150;
                    transform->velocity.x = 0;
                    sprite->Play("UpAnimation");
                }
                if(keyCode.compare(rightKey)==0){
                    transform->velocity.y = 0;
                    transform->velocity.x = 150;
                    sprite->Play("RightAnimation");
                }
                if(keyCode.compare(downKey)==0){
                    transform->velocity.y = 150;
                    transform->velocity.x = 0;
                    sprite->Play("DownAnimation");
                }
                if(keyCode.compare(leftKey)==0){
                    transform->velocity.y = 0;
                    transform->velocity.x = -150;
                    sprite->Play("LeftAnimation");
                }
                if(keyCode.compare(shootKey)==0){
                    //TODO:
                }
            }

            if(Game::event.type==SDL_KEYUP){
                std::string keyCode = patch::to_string(Game::event.key.keysym.sym);
                if(keyCode.compare(upKey)==0){
                    transform->velocity.y = 0;
                }
                if(keyCode.compare(rightKey)==0){
                    transform->velocity.x = 0;
                }
                if(keyCode.compare(downKey)==0){
                    transform->velocity.y = 0;
                }
                if(keyCode.compare(leftKey)==0){
                    transform->velocity.x = 0;
                }
            }
        }

        std::string upKey;
        std::string downKey;
        std::string rightKey;
        std::string leftKey;
        std::string shootKey;
        TransformComponent *transform;
        SpriteComponent *sprite;
};