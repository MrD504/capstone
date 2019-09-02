#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Animation.h"

class SpriteComponent : public Component {
	private:
		SDL_Texture* texture;
		SDL_Rect srcRect;
		SDL_Rect dstRect;
		TransformComponent* transform;
		bool isAnimated;
		int numFrames;
		int animationSpeed;
		bool isFixed;
		std::map<std::string, Animation> animations;
		std::string currentAnimationName;
		unsigned int animationIndex = 0;
	public: 
		SDL_RendererFlip spriteFlip;
		SpriteComponent(const char* filePath) {
			isAnimated = false;
			isFixed = false;
			SetTexture(filePath);
		}

		SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
			isAnimated = true;
			this->numFrames = numFrames;
			this->animationSpeed = animationSpeed;
			this->isFixed = isFixed;

			if(hasDirections) {
				Animation downAnimation = Animation(0, numFrames, animationSpeed);	
				Animation rightAnimation = Animation(1, numFrames, animationSpeed);	
				Animation leftAnimation = Animation(2, numFrames, animationSpeed);	
				Animation upAnimation = Animation(3, numFrames, animationSpeed);
	
				animations.emplace("downAnimation", downAnimation);
				animations.emplace("rightAnimation", rightAnimation);
				animations.emplace("leftAnimation", leftAnimation);
				animations.emplace("upAnimation", upAnimation);

				this->animationIndex = 0;
				this->currentAnimationName = "downAnimation";
			} else {
				Animation singleAnimation(0, numFrames, animationSpeed);
				animations.emplace("SingleAnimation", singleAnimation);
				this->animationIndex = 0;
				this->currentAnimationName = "SingleAnimation";
			}

			Play(this->currentAnimationName);
			SetTexture(id);
		}	

		void Play(std::string animationName) {
			numFrames = animations[animationName].numFrames;
			animationIndex = animations[animationName].index;
			animationSpeed = animations[animationName].animationSpeed;
			currentAnimationName = animationName;
		}

		void SetTexture(std::string assetTextureId) {
			texture = Game::assetManager->GetTexture(assetTextureId);
		}

		void Initialize() override {
			transform = owner->GetComponent<TransformComponent>();
			srcRect.x = 0;
			srcRect.y = 0;
			srcRect.w = transform->width;
			srcRect.h = transform->height;
		}

		void Update(float deltaTime) override {
			if(isAnimated) {
				srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
			}
			srcRect.y = animationIndex * transform->height;

			dstRect.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);
			dstRect.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
			dstRect.w = transform->width * transform->scale;
			dstRect.h = transform->height * transform->scale;
		}

		void Render() override {
			TextureManager::Draw(texture, srcRect, dstRect, spriteFlip);
		}
};


#endif
