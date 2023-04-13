#include "input.h"
#include <SDL.h>
#include <stdio.h>
#include "entity.h"
#include "projectile.h"
#include "player.h"
#include "setup.h"
#include "util.h"
#include "enemy.h"

bool is_fire = false;

void get_key_down(SDL_KeyboardEvent* event);
void get_key_up(SDL_KeyboardEvent* event);

void get_input()
{
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				get_key_down(&e.key);
				break;

			case SDL_KEYUP:
				get_key_up(&e.key);
				break;

			default:
				break;
		}
	}
}

void get_key_down(SDL_KeyboardEvent* event)
{
	if (!event->repeat && player) {
		switch (event->keysym.scancode) {
			//Arrrow keys
			case SDL_SCANCODE_UP:
				player->vel.y -= 1;
				break;
			case SDL_SCANCODE_DOWN:
				player->vel.y += 1;
				break;
			case SDL_SCANCODE_LEFT:
				player->vel.x -= 1;
				break;
			case SDL_SCANCODE_RIGHT:
				player->vel.x += 1;
				break;

			//WASD
			case SDL_SCANCODE_W:
				player->vel.y -= 1;
				break;
			case SDL_SCANCODE_S:
				player->vel.y += 1;
				break;
			case SDL_SCANCODE_A:
				player->vel.x -= 1;
				break;
			case SDL_SCANCODE_D:
				player->vel.x += 1;
				break;

			//Fire bullet
			case SDL_SCANCODE_E:
				is_fire = true;
				break;

			//Suicide and respawn
			case SDL_SCANCODE_Q:
				destroy_entity_list(&bullet_list);
				destroy_entity_list(&enemy_list);
				break;
			
		}
	} else if (!player && (event->keysym.scancode == SDL_SCANCODE_R)) {
		create_player();
	}
}

void get_key_up(SDL_KeyboardEvent* event)
{
	if (!event->repeat && player) {
		switch (event->keysym.scancode) {
			//Arrow keys
			case SDL_SCANCODE_UP:
				player->vel.y += 1;
				break;
			case SDL_SCANCODE_DOWN:
				player->vel.y -= 1;
				break;
			case SDL_SCANCODE_LEFT:
				player->vel.x += 1;
				break;
			case SDL_SCANCODE_RIGHT:
				player->vel.x -= 1;
				break;

			//WASD
			case SDL_SCANCODE_W:
				player->vel.y += 1;
				break;
			case SDL_SCANCODE_S:
				player->vel.y -= 1;
				break;
			case SDL_SCANCODE_A:
				player->vel.x += 1;
				break;
			case SDL_SCANCODE_D:
				player->vel.x -= 1;
				break;
			
			//Fire bullet
			case SDL_SCANCODE_E:
				is_fire = false;
				player->countdown = 0;
				break;
		}
	}
}