#include <iostream>
#include "AssetManager.h"
#include "Constants.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Game.h"
#include "Map.h"
#include "../lib/glm/glm.hpp"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/TextLabelComponent.h"
#include "./Components/ProjectileEmitterComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
bool Game::debugMode = false;
SDL_Event Game::event;
SDL_Rect Game::camera = {0,0, WINDOW_WIDTH, WINDOW_HEIGHT};
Entity& playerEntity(manager.AddEntity("chopper", PLAYER_LAYER));
Map *map;

Game::Game(){
    this->isRunning = false;
    this->ticksLastFrame =0;
}

Game::~Game(){}

void Game::Initialize(int width, int height){
    //Attempt to initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        std::cerr<<"Error Initializing SDL"<<std::endl;
        return;
    }
    if(TTF_Init()!=0){
        std::cerr<<"Error Initializing SDL TTF"<<std::endl;
    }
    //Attempt to create window
    window = SDL_CreateWindow("Gyro Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width, height,SDL_WINDOW_BORDERLESS);
    if(!window){
        std::cerr<<"Failed to Create Window"<<std::endl;
        return;
    }
    //Attempt to create render
    renderer = SDL_CreateRenderer(window,-1,0);
    if(!renderer){
        std::cerr<<"Failed to Create Renderer"<<std::endl;
        return;
    }

    LoadLevel(0);


    //Engine/Game have successfully been initialized
    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber){

    /*start including new assets to the assetmanager list*/
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
    assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
    assetManager->AddTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
    assetManager->AddTexture("projectile-image", std::string("./assets/images/bullet-enemy.png").c_str());
    assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);

    map = new Map("jungle-tiletexture", 2, 32);
    map->LoadMap("./assets/tilemaps/jungle.map",25,20);

    /*start creating entities and also components to them*/
    Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
    tankEntity.AddComponent<TransformComponent>(150,495,5,0,32,32,1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");
    tankEntity.AddComponent<ColliderComponent>("ENEMY", 0,0,32,32);

    Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
    projectile.AddComponent<TransformComponent>(150+16, 495+16,0,0,4,4,1);
    projectile.AddComponent<SpriteComponent>("projectile-image");
    projectile.AddComponent<ColliderComponent>("PROJECTILE",150+16,495+16,4,4);
    projectile.AddComponent<ProjectileEmitterComponent>(50,270,200,true);

    playerEntity.AddComponent<TransformComponent>(240,106,0,0,32,32,1);
    playerEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    playerEntity.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
    playerEntity.AddComponent<ColliderComponent>("PLAYER", 240, 106, 32,32);

    //End level entity*/
    Entity& heliport(manager.AddEntity("Heliport", OBSTACLE_LAYER));
    heliport.AddComponent<TransformComponent>(470,420,0,0,32,32,1);
    heliport.AddComponent<SpriteComponent>("heliport-image");
    heliport.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32,32);

    Entity& radarEntity(manager.AddEntity("Radar", UI_LAYER));
    radarEntity.AddComponent<TransformComponent>(720,15,0,0,64,64,1);
    radarEntity.AddComponent<SpriteComponent>("radar-image", 8,150,false,true);

    Entity& labelLevelName(manager.AddEntity("LabelLevelName", UI_LAYER));
    labelLevelName.AddComponent<TextLabelComponent>(10,10, "First Level...", "charriot-font",GREEN_COLOR);
}


void Game::ProcessInput(){
    //create and pool event
    SDL_PollEvent(&event);
    //check event type
    switch(event.type){
        case SDL_QUIT:
            isRunning= false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                isRunning=false;
            }
            if(event.key.keysym.sym==SDLK_F1){
                debugMode = !debugMode;
            }
            break;
        default:
            break;
    }
}

void Game::Update(){
    //Sleep the execution until we reach the target frame time in milliseconds
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks()-ticksLastFrame);

    //Only call delay if we are too fast to process this frame
    if(timeToWait > 0 && timeToWait <=FRAME_TARGET_TIME){
        SDL_Delay(timeToWait);
    }

    //difference from last frame to current frame converted to seconds
    float deltaTime = (SDL_GetTicks()-ticksLastFrame)/ 1000.0f;

    /*Clamp deltaTime to a maximum value, avoids problems when debugging causing deltaTime to get
    ridiculously huge due to SDL_GetTicks() still increasing in the background while ticksLastFrame
    stays at the same value for a long chunk of time*/
    deltaTime = (deltaTime>0.05f) ? 0.05f : deltaTime;

    //get current ticks at this point of frame from time of init in ms
    //used in next pass
    ticksLastFrame = SDL_GetTicks();

    //loop all entities in the manager, which in turn run the update function 
    //of their respective components
    manager.Update(deltaTime);

    //moves camera
    HandleCameraMovement();

    //check collisions
    CheckCollisions();
}

void Game::Render(){
    //set background color
    SDL_SetRenderDrawColor(renderer, 21,21,21,255);
    //clear back buffer
    SDL_RenderClear(renderer);

    //if no entities present, return. there is no need to waste processing time
    if(manager.hasNoEntities()){
        return;
    }
    //loop all entities in the manager, which in turn run the render function
    //of their respective components
    manager.Render();

    //Swap the back buffer with front buffer
    SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement(){
    TransformComponent* mainPlayerTransform = playerEntity.GetComponent<TransformComponent>();
    
    //update camera position based on window dimensions and player position
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH/2);
    camera.y= mainPlayerTransform->position.y-(WINDOW_HEIGHT/2);

    //Clamping the values of the camera
    camera.x = camera.x<0 ? 0 : camera.x;
    camera.y = camera.y<0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w: camera.x;
    camera.y = camera.y > camera.h ? camera.h: camera.y;
}

void Game::CheckCollisions(){
    CollisionType collisionType =manager.CheckCollisions();

    //std::cout<<collisionType<<std::endl;
    if(collisionType==PLAYER_ENEMY_COLLISION){
        ProcessGameOver();
    }
    if(collisionType==PLAYER_LEVEL_COMPLETE_COLLISION){
        ProcessNextLevel(1);
    }
}

void Game::ProcessNextLevel(int levelNumber){
    std::cout<<"Next Level"<<std::endl;
    isRunning =false;
}

void Game::ProcessGameOver(){
    std::cout<<"Game Over"<<std::endl;
    isRunning = false;
}

void Game::Destroy(){
    //Destroy render, window and exit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

