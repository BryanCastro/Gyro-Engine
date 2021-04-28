#pragma once
#include <SDL2/SDL.h>
#include "../Game.h"
#include "../Component.h"
#include "./TransformComponent.h"


class ColliderComponent: public Component{
    public:
        ColliderComponent(std::string colliderTag, int x, int y, int width, int height){
            this->colliderTag=colliderTag;
            this->collider={x,y,width,height};
        }

        void Initialize() override{
            if(owner->HasComponent<TransformComponent>()){
                transform = owner->GetComponent<TransformComponent>();
                srcRect ={0,0,transform->width, transform->height};
                destRect ={collider.x, collider.y, collider.w, collider.h};
            }
           
        }

        void Update(float deltaTime) override{

            //update collider position based on entity position and scale
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;

            //update destRect of collider
            destRect.x = collider.x - Game::camera.x;
            destRect.y = collider.y - Game::camera.y;
        }

        std::string colliderTag;
        SDL_Rect collider;
        SDL_Rect srcRect;
        SDL_Rect destRect;
        TransformComponent* transform;
};