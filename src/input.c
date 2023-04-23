#include "input.h"
#include <SDL.h>
#include <stdio.h>
#include "entity.h"
#include "projectile.h"
#include "player.h"
#include "setup.h"
#include "util.h"
#include "enemy.h"

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
			case SDL_SCANCODE_W:
				player->entity.vel.y -= 1;
				break;
			case SDL_SCANCODE_DOWN: 
			case SDL_SCANCODE_S:
				player->entity.vel.y += 1;
				break;
			case SDL_SCANCODE_LEFT: 
			case SDL_SCANCODE_A:
				player->entity.vel.x -= 1;
				//player->facing_right = 0;
				break;
			case SDL_SCANCODE_RIGHT: 
			case SDL_SCANCODE_D:
				player->entity.vel.x += 1;
				//player->facing_right = 1;
				break;

			//Fire bullet
			case SDL_SCANCODE_E:
				player->is_fire = true;
				break;

			//Suicide and respawn
			case SDL_SCANCODE_Q:
				destroy_bullet_list();
				destroy_enemy_list();
				break;
			
		}
	} else if (!player && (event->keysym.scancode == SDL_SCANCODE_R)) {
		spawn_player();
	}
}

void get_key_up(SDL_KeyboardEvent* event)
{
	if (!event->repeat && player) {
		switch (event->keysym.scancode) {
			//Arrow keys
			case SDL_SCANCODE_UP: 
			case SDL_SCANCODE_W:
				player->entity.vel.y += 1;
				break;
			case SDL_SCANCODE_DOWN: 
			case SDL_SCANCODE_S:
				player->entity.vel.y -= 1;
				break;
			case SDL_SCANCODE_LEFT: 
			case SDL_SCANCODE_A:
				player->entity.vel.x += 1;
				break;
			case SDL_SCANCODE_RIGHT: 
			case SDL_SCANCODE_D:
				player->entity.vel.x -= 1;
				break;
			
			//Fire bullet
			case SDL_SCANCODE_E:
				player->is_fire = false;
				player->entity.countdown = 0;
				break;
		}
	}
}