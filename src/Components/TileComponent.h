#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include <SDL2/SDL.h>
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../../lib/glm/glm.hpp"

class TileComponent : public Component {
	public:
		SDL_Texture* texture;
		SDL_Rect srcRect;
		SDL_Rect dstRect;
		glm::vec2 position;	

		TileComponent(int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId) {
			texture = Game::assetManager->GetTexture(assetTextureId);

			srcRect.x = srcRectX;
			srcRect.y = srcRectY;
			srcRect.h = srcRect.w = tileSize;

			dstRect.x = x;
			dstRect.y = y;
			dstRect.w = dstRect.h = tileSize * tileScale;

			position.x = x;
			position.y = y;
		}

		~TileComponent() {}

		void Update(float deltaTime) override {
			//TODO: this is where we are going to take care of the tile positions
			//based on the camera control that will keep moving around
			dstRect.x = position.x - Game::camera.x;
			dstRect.y = position.y - Game::camera.y;	
		};

		void Render() override {
			TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);	
		};

		void Initialize() override {};
};

#endif
