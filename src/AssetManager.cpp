#include "AssetManager.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "SDL2/SDL.h"

AssetManager::AssetManager(EntityManager* manager): manager(manager){
    
}

AssetManager::~AssetManager(){}

//clears all textures from map
void AssetManager::ClearData(){
    textures.clear();
}

/*takes a texture ID as the key to map, then calls static function loadTexture located in TextureManager
that loads the texture and returns a reference to it which is then stored in the map*/
void AssetManager::AddTexture(std::string textureID, const char* filePath){
    textures.emplace(textureID, TextureManager::LoadTexture(filePath));
}

//Returns a texture by accessing it in the map via its ID
SDL_Texture* AssetManager::GetTexture(std::string textureID){
    return textures[textureID];
}
