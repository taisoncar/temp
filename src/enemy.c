#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "setup.h"
#include "entity.h"
#include "util.h"
#include "projectile.h"
#include "player.h"

#define ENEMY_SPEED 100.0f
#define ENEMY_RELOAD 60
#define ENEMY_HEALTH 1

Enemy_list enemy_list;

void init_enemy_list()
{
    enemy_list.head.next = NULL;
    enemy_list.tail = &enemy_list.head;
}

void destroy_enemy_list()
{
	Enemy *prev = &enemy_list.head;
	for (Enemy *i = enemy_list.head.next; i != NULL; i = i->next) {
		if (i == enemy_list.tail) {
			enemy_list.tail = prev;
		}
		prev->next = i->next;
		free(i);
		i = prev;
	}
}

void spawn_enemy()
{

	Enemy *new_enemy = malloc(sizeof(Enemy));
	assert(new_enemy);

	enemy_list.tail = enemy_list.tail->next = new_enemy;
	new_enemy->next = NULL;

	//Setup enemy entity struct
	new_enemy->entity.texture = g_texture[T_ENEMY];

    SDL_QueryTexture(new_enemy->entity.texture, NULL, NULL, &new_enemy->entity.w, &new_enemy->entity.h);
    new_enemy->entity.w /= 2;
    new_enemy->entity.h /= 2;

    new_enemy->entity.pos.x = rand_range(0, SCREEN_WIDTH - new_enemy->entity.w);
    new_enemy->entity.pos.y = 0;

    new_enemy->entity.vel.x = 0.0f;
    new_enemy->entity.vel.y = 1.0f;
    new_enemy->entity.speed = ENEMY_SPEED;

    new_enemy->entity.health = ENEMY_HEALTH;
    new_enemy->entity.side = ENEMY_SIDE;
    new_enemy->entity.countdown = 0;
}

void update_enemies(float delta_time)
{
	Enemy *prev = &enemy_list.head;
	for (Enemy *i = enemy_list.head.next; i != NULL; i = i->next) {
		update_entity(&i->entity, delta_time);
		
		//Fire bullet if not reloading
		if ((i->entity.countdown-- <= 0) && player) {
			spawn_bullet(i->entity);
			i->entity.countdown = ENEMY_RELOAD;
		}

		//Delete enemy if out of bound / killed
		if ( (i->entity.pos.y > SCREEN_HEIGHT) || (i->entity.health <= 0) ) {
			if (i == enemy_list.tail) {
				enemy_list.tail = prev;
			}
			prev->next = i->next;
			free(i);
			i = prev;
		}
		prev = i;
	}
}

void draw_enemies()
{
	for (Enemy *i = enemy_list.head.next; i != NULL; i = i->next) {
		draw_entity(i->entity);
		SDL_Color blue = {0xFC, 0x29, 0x47, 0xFF};
		draw_rect(get_entity_rect(i->entity), &blue);
	}
}
