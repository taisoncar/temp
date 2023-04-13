#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "setup.h"
#include "input.h"
#include "entity.h"
#include "projectile.h"
#include "player.h"
#include "message.h"
#include "enemy.h"
#include "util.h"

void init();
void update(double delta_time);
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

		calc_fps();
		limit_fps();
	}

	return 0;
}

void init()
{
	//Init system and resources
	init_SDL();
	init_texture();
	load_font();

	//Init entities
	create_player();
	init_bullet();
	init_enemy();

	//Init ui
	init_message();
}

void update(double delta_time)
{
	update_player(delta_time);
	update_bullets(delta_time);
	update_enemies(delta_time);
	update_messages();
}

void draw()
{
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 255);
	SDL_RenderClear(g_renderer);
	//////////////////////////

	draw_entity(player);
	if (player) {
		draw_rect(get_entity_rect(player));
	}
	render_bullets();
	render_enemies();
	draw_messages();

	///////////////////////////
	SDL_RenderPresent(g_renderer);
}