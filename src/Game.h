#ifndef GAME_H
#define GAME_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

class AssetManager;

class Game {
    private:
        SDL_Window *window;
        bool isRunning;
				int ticksLastFrame;
    public:
        Game();
        ~Game();
        bool IsRunning() const;
        void Initialize(int width, int height);
        void ProcessInput();
				void LoadLevel(int levelNumber);
        void Update();
        void Render();
				void HandleCameraMovement();
				void CheckCollisions();
				void ProcessGameOver();
				void ProcessNextLevel(int levelNum);
        static SDL_Renderer* renderer;
				static AssetManager* assetManager;
				static SDL_Event event;
				static SDL_Rect camera;
        void Destroy();
};

#endif
