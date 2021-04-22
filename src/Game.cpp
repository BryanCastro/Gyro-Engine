#include <iostream>
#include "AssetManager.h"
#include "Constants.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Game.h"
#include "../lib/glm/glm.hpp"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;

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

    /*start creating entities and also components to them*/
    Entity& tankEntity(manager.AddEntity("tank"));
    tankEntity.AddComponent<TransformComponent>(0,0,20,20,32,32,1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");

    Entity& chopperEntity(manager.AddEntity("chopper"));
    chopperEntity.AddComponent<TransformComponent>(240,106,0,0,32,32,1);
    chopperEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    chopperEntity.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");

    Entity& radarEntity(manager.AddEntity("Radar"));
    radarEntity.AddComponent<TransformComponent>(720,15,0,0,64,64,1);
    radarEntity.AddComponent<SpriteComponent>("radar-image", 8,150,false,true);
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

void Game::Destroy(){
    //Destroy render, window and exit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
