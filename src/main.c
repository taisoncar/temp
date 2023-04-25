#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "setup.h"
#include "input.h"
#include "entity.h"
#include "projectile.h"
#include "player.h"
#include "message.h"
#include "enemy.h"
#include "util.h"
#include "camera.h"

void init();
void update(float delta_time);
void draw();

int main(int argc, char* argv[])
{
	//Exit
	atexit(close_SDL);

	init();

	//Main game loop
	while (1) {
		get_input();
		update(frame_time / 1000.0f);
		draw();

		limit_fps();
		calc_fps();
	}

	return 0;
}

void init()
{
	//Init system and resources
	init_SDL();
	init_texture();
	load_font();

	//Init entities and lists
	init_enemy_list();
	init_bullet_list();
	spawn_player();

	//Init ui
	init_messages();
}

void update(float delta_time)
{
	static int cooldown = 0;
	if (cooldown-- <= 0) {
		spawn_enemy(); 
		cooldown = 100;
	}
	update_camera();

	update_bullets(delta_time);
	update_player(delta_time);
	update_enemies(delta_time);
	update_messages();
}

void draw()
{
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 255);
	SDL_RenderClear(g_renderer);
	//////////////////////////
	//SDL_RenderSetScale(g_renderer, 5.0f, 5.0f);
	draw_bullets();
	draw_enemies();
	draw_player();
	draw_messages();

	SDL_Rect bound = {
		0, 
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
	};
	SDL_Color blue = {0xFC, 0x29, 0x47, 0xFF};
	draw_rect(world_to_screen(bound), &blue);


	///////////////////////////
	SDL_RenderPresent(g_renderer);
}