#pragma once
#include "../Component.h"
#include "../Game.h"
#include "SDL2/SDL.h"
#include "../../lib/glm/glm.hpp"

class TransformComponent: public Component{
    public:
        TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s){
            position = glm::vec2(posX, posY);
            velocity = glm::vec2(velX,velY);
            width = w;
            height = h;
            scale = s;
        }

        void Initialize() override{}

        void Update(float deltaTime) override{
            
            //update the position as a function of delta time
            position.x +=velocity.x * deltaTime;
            position.y +=velocity.y * deltaTime;
        }

        void Render() override{
            SDL_Rect transformRectangle ={
                static_cast<int>(position.y),
                static_cast<int>(position.x),
                width,
                height
            };
            SDL_SetRenderDrawColor(Game::renderer, 255,255,255,255);
            SDL_RenderFillRect(Game::renderer, &transformRectangle);

        }

        glm::vec2 position;
        glm::vec2 velocity;
        int width;
        int height;
        int scale;
};