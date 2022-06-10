#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	bool isDash = false;
	int dash = 0;
	int moveX = 0;
	int moveY = 0;
	int stopX = 0;
	int stopY = 0;


	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		
		//std::cout << dash << std::endl;
		if (isDash == true) {
			
			if (dash <= 2) {
				dash += 1;
			}
			else {
				dash = 0;
				isDash = false;
			}
		}

		if (Game::event.type == SDL_KEYDOWN)
		{
			if (state[SDL_SCANCODE_SPACE]) {
				if (isDash == false) {
					dash = 0;
					isDash = true;
				}
			}
			if (state[SDL_SCANCODE_ESCAPE]) {
				Game::isRunning = false;
			}
		}

		if (state[SDL_SCANCODE_RIGHT]) {
			moveX = 1;
			sprite->Play("Walk");
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
		}
		else {
			if (state[SDL_SCANCODE_LEFT]) {
				moveX = -1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
			}
			else {
				stopX = moveX;
				moveX = 0;
				
			}
		}
		if (state[SDL_SCANCODE_UP]) {
			moveY = -1;
			sprite->Play("WalkUp");
		}
		else {
			if (state[SDL_SCANCODE_DOWN]) {
				moveY = 1;
				sprite->Play("WalkDown");
			}
			else {
				stopY = moveY;
				moveY = 0;
			}
		}
		//std::cout << stopY << "," << moveX << std::endl;
		//std::cout << stopX << "'" << moveY << std::endl;

		if ((moveY == 0) && (moveX == 0)) {
			switch (stopY)
			{
			case 0:
				switch (stopX)
				{
				case 1:
					sprite->Play("Idle");
					break;
				case -1:
					sprite->Play("Idle");
					break;
				default:
					break;
				}
			break;


			case 1:
				sprite->Play("IdleDown");
			break;

			case -1:
				sprite->Play("IdleUp");
			break;
			default:
				break;
			}
		}



		if (isDash == true) {
			transform->velocity.y = 8*moveY;
			transform->velocity.x = 8*moveX;
		}
		else {
			transform->velocity.y = 1*moveY;
			transform->velocity.x = 1*moveX;
		}
	}
};