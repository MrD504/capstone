#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponents.h"

class ColliderComponent : public Component {
	public:
		std::string colliderTag;
		SDL_Rect collider;
		SDL_Rect srcRect;
		SDL_Rect dstRect;	
		TransformComponent* transform;

		ColliderComponent(std::string colliderTag, int x, int y, int width, int height){
			this->colliderTag = colliderTag;
			this->collider = {x, y, width, height};			
		};
		~ColliderComponent();

		void Initialize() override {
			if(owner->HasComponent<TransformComponent>()) {
				transform = owner->GetComponent<TransformComponent>();
				srcRect = { 0, 0, transform->width, transform->height };
				dstRect = { collider.x, collider.y, collider.w, collider.h };
			}	
		};
		void Render() override {};
		void Update(float deltaTime) override {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;

			dstRect.x = collider.x - Game::camera.x;
			dstRect.y = collider.y - Game::camera.y;	
		};
};

#endif
