#include <fstream>
#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include "./Components/TileComponent.h"

extern EntityManager manager;
Map::Map(std::string textureId, int scale, int tileSize){
    this->textureId=textureId;
    this->scale = scale;
    this->tileSize=tileSize;
}

//read the map tile definitions from the .map file
void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY){
    std::fstream mapFile;
    mapFile.open(filePath);

    for(int row =0;row<mapSizeY;row++){
        for(int col = 0;col<mapSizeX;col++){
            char ch;
            mapFile.get(ch);
            int sourceRectY = atoi(&ch)*tileSize;
            mapFile.get(ch);
            int sourceRectX = atoi(&ch)*tileSize;
            AddTile(sourceRectX, sourceRectY,col*(scale*tileSize),row*(scale*tileSize));
            mapFile.ignore();
        }
    }
    mapFile.close();
}

//Add a new title entity in the game scene
void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y){
    Entity& newTile(manager.AddEntity("Tile", TILEMAP_LAYER));
    newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y,tileSize, scale, textureId);
}