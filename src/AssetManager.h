#pragma once

#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

class FontManager;
class TextureManager;
class EntityManager;
class SDL_Texture;

class AssetManager{
    public:
        AssetManager(EntityManager* manager);
        ~AssetManager();
        void ClearData();
        void AddTexture(std::string textureID, const char* filePath);
        SDL_Texture* GetTexture(std::string textureID);
        void AddFont(std::string fontID, const char* filePath, int fontSize);
        TTF_Font* GetFont(std::string fontID);
    private:
        EntityManager* manager;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;
};