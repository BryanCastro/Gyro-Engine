#include <iostream>
#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName){
    //attempted to create surface and check if successfully created
    SDL_Surface* surface = IMG_Load(fileName);
    if(!surface){
        std::cerr<<"Failed to Create Surface!!"<<std::endl;
        return NULL;
    }
    //attempt to create texture and check if successfully created
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    if(!texture){
        std::cerr<<"Failed to Create Texture!!"<<std::endl;
        return NULL;
    }
    //free the surface
    SDL_FreeSurface(surface);
    //return the texture
    return texture;
}

void TextureManager:: Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip){
    SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect, 0.0, NULL, flip);
}