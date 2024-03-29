#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "Map.h"
#include "AssetManager.h"
#include "Components/TransformComponents.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

Game::Game(){
    this->isRunning = false;
};
Game::~Game(){};

bool Game::IsRunning() const { return this->isRunning; }

void Game::Initialize(int width, int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << " Error initializing SDL" << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );

    if(!window) {
        std::cerr << "Window failed to initialize" << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer) {
        std::cerr << "Renderer failed to initialize" << std::endl;
        return;
    }


		LoadLevel(0);
    isRunning = true;
    return;
}

Entity& player(manager.AddEntity("helo", PLAYER_LAYER));

void Game::LoadLevel(int levelNumber) {
	// TODO: Start adding assets to asset manager list
	assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
	assetManager->AddTexture("helo-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
	assetManager->AddTexture("jungle-tilemap", std::string("./assets/tilemaps/jungle.png").c_str());

	map = new Map("jungle-tilemap", 2, 32);
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

	//add entities and add components to entities
	Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
	tankEntity.AddComponent<TransformComponent>(150, 495, 10, 0, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("tank-image");
	tankEntity.AddComponent<ColliderComponent>("ENEMY", 150, 495, 32, 32);

	player.AddComponent<TransformComponent>(240, 160, 0, 0, 32, 32, 1);
	player.AddComponent<SpriteComponent>("helo-image", 2, 90, true, false);
  player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
	player.AddComponent<ColliderComponent>("PLAYER", 240, 160, 32, 32);
	
	Entity& radarEntity(manager.AddEntity("radar", UI_LAYER));
	radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
	manager.ListAllEntities();
}

void Game::ProcessInput() {
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
		}
		default: {
			break;
		}
	}
}

void Game::Update(){
	// Wait until 16ms has ellapsed since the last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));		

	// delta time is the difference in ticks from the last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	// clamp delta time to a maximum value (good for when using breakpoints)
	deltaTime = (deltaTime > 0.05f) ? 0.05f: deltaTime;

	// set the new ticks for the current frame to be used in the next pass
	ticksLastFrame = SDL_GetTicks();

	// Here we call the manager update to update all entities passing delta time
	manager.Update(deltaTime);

	HandleCameraMovement();
	CheckCollisions();
}

void Game::HandleCameraMovement() {
	TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();
	camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
	camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT /2);

	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions() {
	CollisionType collisionType = manager.CheckCollisions();
	if(collisionType == PLAYER_ENEMY_COLLISION) {
		ProcessGameOver();
	}
	if(collisionType == PLAYER_LEVEL_COLLISION) {
		ProcessNextLevel(1);
	}
}
				
void Game::ProcessGameOver() {
	std::cout << "Oh bugger! Better luck next time" << std::endl;
	isRunning = false;
}

void Game::ProcessNextLevel(int levelNum) {
	std::cout << "Congratulations you got to the next level" << levelNum << std::endl;
	isRunning = false;
};

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// Here we call the manager renderer to render all entities
	if (manager.HasNoEntities()) {
		return;
	}

	manager.Render();	
	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};
