#include <iostream>
#include "./Constants.h"
#include "Game.h"

float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 0.01f;
float projectileVelY = 0.01f;

Game::Game(){
    this->isRunning = false;
}

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
    projectilePosX += projectileVelX;
    projectilePosY += projectileVelY;
}

void Game::Render(){
    //set background color
    SDL_SetRenderDrawColor(renderer, 21,21,21,255);
    //clear back buffer
    SDL_RenderClear(renderer);

    SDL_Rect projectile {
        (int) projectilePosX,
        (int) projectilePosY,
        10,
        10
    };

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
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