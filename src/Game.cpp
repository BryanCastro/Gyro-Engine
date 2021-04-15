#include <iostream>
#include "./Constants.h"
#include "Game.h"
#include "../lib/glm/glm.hpp"

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVel = glm::vec2(20.0f, 20.0f);

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
    //Engine/Game have successfully been initialized
    isRunning = true;
    return;
}

void Game::ProcessInput(){
    //create and pool event
    SDL_Event event;
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

    //use DeltaTime to update game objects
    projectilePos =  glm::vec2(projectilePos.x + projectileVel.x*deltaTime, projectilePos.y + projectileVel.y * deltaTime);
}

void Game::Render(){
    //set background color
    SDL_SetRenderDrawColor(renderer, 21,21,21,255);
    //clear back buffer
    SDL_RenderClear(renderer);

    SDL_Rect projectile {
        static_cast<int>(projectilePos.x),
        static_cast<int>(projectilePos.y),
        10,
        10
    };

    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderFillRect(renderer, &projectile);

    //Swap the back buffer with front buffer
    SDL_RenderPresent(renderer);
}

void Game::Destroy(){
    //Destroy render, window and exit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

