#pragma once
#include "SDL2/SDL.h"
#include "../TextureManager.h"
#include "../Animation.h"
#include "../AssetManager.h"
#include "../Component.h"
#include "TransformComponent.h"

class SpriteComponent: public Component{
    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent(std::string assetTextureID){
            isAnimated = false;
            isFixed = false;
            SetTexture(assetTextureID);
        }

        SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed){
            isAnimated = true;
            this->numFrames = numFrames;
            this->animationSpeed = animationSpeed;
            this->isFixed = isFixed;

            if(hasDirections){
                Animation downAnimation = Animation(0, numFrames, animationSpeed);
                Animation rightAnimation = Animation(1, numFrames, animationSpeed);
                Animation leftAnimation = Animation(2, numFrames, animationSpeed);
                Animation upAnimation = Animation(3, numFrames, animationSpeed);

                animations.emplace("DownAnimation", downAnimation);
                animations.emplace("RightAnimation", rightAnimation);
                animations.emplace("LeftAnimation", leftAnimation);
                animations.emplace("UpAnimation", upAnimation);

                this->animationIndex = 0;
                this->currentAnimationName = "DownAnimation";
            }else{
                Animation singleAnimation = Animation(0, numFrames, animationSpeed);
                animations.emplace("SingleAnimation", singleAnimation);
                this->animationIndex =0;
                this->currentAnimationName = "SingleAnimation";
            }

            Play(this->currentAnimationName);
            SetTexture(id);
        }

        void Play(std::string animationName){
            numFrames = animations[animationName].numFrames;
            animationIndex = animations[animationName].index;
            animationSpeed = animations[animationName].animationSpeed;
            currentAnimationName = animationName;
        }

        void SetTexture(std::string assetTextureID){
            texture = Game::assetManager->GetTexture(assetTextureID);
            if(texture==nullptr){
                std::cerr<<"Error: Failed to load Texture "<<assetTextureID<<std::endl;
                std::cerr<<"Either Texture does not exist or typo when adding AddTexture and/or SpriteComponent"<<std::endl;
            }
        };

        void Initialize() override{
            transform= owner->GetComponent<TransformComponent>();
            srcRect.x = 0;
            srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;
        };

        void Update(float deltaTime) override{
        
            if(isAnimated){
                srcRect.x  = srcRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) %numFrames);
            }
            srcRect.y = animationIndex * transform->height;

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
        bool isAnimated;
        int numFrames;
        int animationSpeed;
        bool isFixed;
        std::map<std::string, Animation> animations;
        std::string currentAnimationName;
        unsigned int animationIndex = 0;
};