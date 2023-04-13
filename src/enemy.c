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

Entity* enemy_head = NULL;
Entity* enemy_tail = NULL;

void spawn_enemy();

void init_enemy()
{
	enemy_head = (Entity*)malloc(sizeof(Entity));
	if (enemy_head == NULL) {
		printf("Insufficient memory");
		exit(1);
	}
	enemy_head->next = NULL;
	enemy_tail = enemy_head;
}

void spawn_enemy()
{
	Entity* new_enemy;

	new_enemy = create_entity(g_texture[T_ENEMY], 0, 0, ENEMY_SPEED, 1, ENEMY_SIDE);
	new_enemy->w /= 2;
	new_enemy->h /= 2;
	new_enemy->pos.x = rand_range(0, SCREEN_WIDTH - new_enemy->w);
	//new_enemy->pos.x = (SCREEN_WIDTH / 2) - (new_enemy->rect.w / 2);
	new_enemy->vel.y += 1;

	enemy_tail->next = new_enemy;
	enemy_tail = enemy_tail->next;
}

void update_enemies(double delta_time)
{
	static int cooldown = 0;
	if (cooldown-- <= 0) {
		spawn_enemy();
		cooldown = 100;
	}

	Entity* b;
	Entity* prev;

	prev = enemy_head;

	for (b = enemy_head->next; b != NULL; b = b->next) {
		update_entity(b, delta_time);
		
		//Fire bullet if not reloading
		if ((b->countdown-- <= 0) && player) {
			fire_bullet(b);
			b->countdown = ENEMY_RELOAD;
		}

		//Delete enemy if out of bound / killed
		if ( (b->pos.y > SCREEN_HEIGHT) || (b->health == 0) ) {
			if (b == enemy_tail) {
				enemy_tail = prev;
			}

			prev->next = b->next;
			destroy_entity(&b);
			b = prev;
		}
		prev = b;
	}
}

void render_enemies()
{
	Entity* b;

	for (b = enemy_head->next; b != NULL; b = b->next) {
		draw_entity(b);
		draw_rect(get_entity_rect(b));
	}
}
