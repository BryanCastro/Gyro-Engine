#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "./TextureManager.h"
#include "./FontManager.h"
#include "./EntityManager.h"
#include "./AudioManager.h"

class AssetManager {
    private:
        EntityManager* manager;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;
        std::map<std::string, Mix_Chunk*> sounds;
        //std::map<std::string, Mix_Music> music;
    public:
        AssetManager(EntityManager* manager);
        ~AssetManager();
        void ClearData();
        
        void AddTexture(std::string textureId, const char* filePath);
        void AddFont(std::string fontId, const char* filePath, int fontSize);        
        void AddSound(std::string soundId, const char* filePath);
        //void AddMusic(std::string musicId, const char* filePath);

        SDL_Texture* GetTexture(std::string textureId);
        TTF_Font* GetFont(std::string fontId);
        Mix_Chunk* GetSound(std::string soundId);
        
};

#endif
