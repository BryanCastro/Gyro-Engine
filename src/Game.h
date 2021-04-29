#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/lua/sol.hpp"

class AssetManager;

class Game{
    public:
        Game();
        ~Game();
        bool IsRunning() const{return isRunning;};
        void LoadLevel(int levelNumber);
        void Initialize(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void HandleCameraMovement();
        void CheckCollisions();
        void ProcessNextLevel(int levelNumber);
        void ProcessGameOver();
        void Destroy();

        static SDL_Renderer *renderer;
        static AssetManager *assetManager;
        static SDL_Event event;
        static SDL_Rect camera;
        static bool debugMode;
        int ticksLastFrame;

    private:
        bool isRunning;
        SDL_Window *window;
        
};