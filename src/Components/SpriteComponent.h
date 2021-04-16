#pragma once
#include "SDL2/SDL.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Component.h"
#include "TransformComponent.h"

class SpriteComponent: public Component{
    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent(const char* filePath){
            SetTexture(filePath);
        }

        void SetTexture(std::string assetTextureID){
            texture = Game::assetManager->GetTexture(assetTextureID);
        };

        void Initialize() override{
            transform= owner->GetComponent<TransformComponent>();
            srcRect.x = 0;
            srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;
        };

        void Update(float deltaTime) override{
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.w = static_cast<int>(transform->width * transform->scale);
            destRect.h = static_cast<int>(transform->height * transform->scale);
        };

        void Render() override{
            TextureManager::Draw(texture, srcRect, destRect,spriteFlip);
        }
    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect srcRect;
        SDL_Rect destRect;
};