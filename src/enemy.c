#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include "setup.h"
#include "entity.h"
#include "util.h"
#include "projectile.h"
#include "player.h"

#define ENEMY_SPEED 100.0f
#define ENEMY_RELOAD 60
#define ENEMY_HEALTH 1

Entity_list enemy_list;

void update_enemy(Entity* enemy, double delta_time);
void draw_enemy(Entity* enemy);

void spawn_enemy()
{
	Entity* new_enemy = create_entity();
	init_enemy(new_enemy);
	add_entity_to_list(new_enemy, &enemy_list);
}

void init_enemy(Entity* enemy)
{
	enemy->id = ENEMY_ID;
	enemy->texture = g_texture[T_ENEMY];

    SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
    enemy->w /= 2;
    enemy->h /= 2;

    enemy->pos.x = rand_range(0, SCREEN_WIDTH - enemy->w);
    enemy->pos.y = 0;

    enemy->vel.x = 0.0f;
    enemy->vel.y = 1.0f;
    enemy->speed = ENEMY_SPEED;

    enemy->health = ENEMY_HEALTH;
    enemy->side = ENEMY_SIDE;
    enemy->countdown = 0;
}

void update_enemies(double delta_time)
{
	for (Entity* i = enemy_list.head->next; i != NULL; i = i->next) {
		update_entity(i, delta_time);
		
		//Fire bullet if not reloading
		if ((i->countdown-- <= 0) && player) {
			spawn_bullet(i);
			i->countdown = ENEMY_RELOAD;
		}

		//Delete enemy if out of bound / killed
		if ( (i->pos.y > SCREEN_HEIGHT) || (i->health == 0) ) {
			remove_entity(&i, &enemy_list);
		}
	}
}

void draw_enemies()
{
	for (Entity* i = enemy_list.head->next; i != NULL; i = i->next) {
		draw_entity(i);
		SDL_Color blue = {0x00, 0x00, 0xFF, 0xFF};
		draw_rect(get_entity_rect(i), &blue);
	}
}
