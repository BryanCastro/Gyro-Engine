#pragma once

#include <map>
#include <string>
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
    private:
        EntityManager* manager;
        std::map<std::string, SDL_Texture*> textures;
};