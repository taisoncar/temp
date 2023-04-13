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

/* Entity* enemy_head = NULL;
Entity* enemy_tail = NULL; */
Entity_list enemy_list;

void spawn_enemy();

void init_enemy()
{
	enemy_list = create_entity_list();
}

void spawn_enemy()
{
	Entity* new_enemy;

	new_enemy = create_entity(g_texture[T_ENEMY], 0, 0, ENEMY_SPEED, 1, ENEMY_SIDE);
	new_enemy->w /= 2;
	new_enemy->h /= 2;
	new_enemy->pos.x = rand_range(0, SCREEN_WIDTH - new_enemy->w);
	new_enemy->vel.y += 1;

	add_entity_to_list(&enemy_list, new_enemy);
}

void update_enemies(double delta_time)
{
	static int cooldown = 0;
	if (cooldown-- <= 0) {
		spawn_enemy();
		cooldown = 100;
	}

	Entity* current;
	Entity* prev;

	prev = enemy_list.head;

	for (current = enemy_list.head->next; current != NULL; current = current->next) {
		update_entity(current, delta_time);
		
		//Fire bullet if not reloading
		if ((current->countdown-- <= 0) && player) {
			fire_bullet(current);
			current->countdown = ENEMY_RELOAD;
		}

		//Delete enemy if out of bound / killed
		if ( (current->pos.y > SCREEN_HEIGHT) || (current->health == 0) ) {
			remove_entity_from_list(&enemy_list, &current, &prev);
		}
		prev = current;
	}
}

void render_enemies()
{
	Entity* b;

	for (b = enemy_list.head->next; b != NULL; b = b->next) {
		draw_entity(b);
		draw_rect(get_entity_rect(b));
	}
}
