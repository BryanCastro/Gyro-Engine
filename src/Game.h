#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
        void Destroy();

        static SDL_Renderer *renderer;
        static AssetManager *assetManager;
        int ticksLastFrame;

    private:
        bool isRunning;
        SDL_Window *window;
        
};