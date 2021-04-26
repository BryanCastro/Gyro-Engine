#pragma once

#include <SDL2/SDL.h>
#include "../Component.h"
#include "../AssetManager.h"
#include "../EntityManager.h"
#include "../TextureManager.h"
#include "../../lib/glm/glm.hpp"

class TileComponent: public Component{
    public:
        SDL_Texture *texture;
        SDL_Rect srcRect;
        SDL_Rect destRect;
        glm::vec2 position;

        TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId){
            texture = Game::assetManager->GetTexture(assetTextureId);
            srcRect.x = sourceRectX;
            srcRect.y = sourceRectY;
            srcRect.w = tileSize;
            srcRect.h = tileSize;

            destRect.x = x;
            destRect.y = y;
            destRect.w = tileSize * tileScale;
            destRect.h = tileSize * tileScale;

            position.x = x;
            position.y = y;
        }

        ~TileComponent(){
            SDL_DestroyTexture(texture);
        }

        //Here is where we take care of the tile positions
        //based on the camera position
        void Update(float deltaTime) override{
            
        }

        //render the texture to the screen
        void Render() override{
            TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
        }
    private:
};