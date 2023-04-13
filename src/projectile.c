#include "projectile.h"
#include <stdio.h>
#include "entity.h"
#include "player.h"
#include "setup.h"
#include "enemy.h"
#include "util.h"

#define BULLET_SPEED 500.0f

Entity* bullet_head = NULL;
Entity* bullet_tail = NULL;
int score = 0;

void init_bullet()
{
	bullet_head = (Entity*)malloc(sizeof(Entity));
	if (bullet_head == NULL) {
		printf("Insufficient memory");
		exit(1);
	}
	bullet_head->next = NULL;
	bullet_tail = bullet_head;
}

void fire_bullet(Entity* entity)
{
	Entity* new_bullet;
	new_bullet = create_entity(g_texture[T_BULLET], entity->pos.x, entity->pos.y, BULLET_SPEED, 1, entity->side);
	new_bullet->w = new_bullet->h = 5;
	new_bullet->countdown = 600;

	if (entity->side == PLAYER_SIDE) {
		new_bullet->pos.x += (entity->w / 2) - (new_bullet->w / 2);
		new_bullet->vel.y -= 1;
	}
	else if (entity->side == ENEMY_SIDE) {
		new_bullet->pos.x += (entity->w / 2) - (new_bullet->w / 2);
		new_bullet->pos.y += entity->h;
		new_bullet->vel = calc_slope(get_entity_center(new_bullet), get_entity_center(player));
		//normalize_vector(&new_bullet->vel);
	}

	bullet_tail->next = new_bullet;
	bullet_tail = bullet_tail->next;
}

void update_bullets(double delta_time)
{
	if (is_fire && player && (player->countdown-- <= 0)) {
		fire_bullet(player);
		player->countdown = PLAYER_RELOAD;
	}
	Entity* b;
	Entity* prev;

	prev = bullet_head;

	for (b = bullet_head->next; b != NULL; b = b->next) {
		// if (b->side == ENEMY_SIDE) {
		// 	b->vel = calc_slope(get_entity_center(b), get_entity_center(player));
		// }
		update_entity(b, delta_time);
		check_bullet_collision(b);

		if ( (b->pos.y < 0) || (b->health == 0) || (b->countdown-- <= 0) ){
			if (b == bullet_tail) {
				bullet_tail = prev;
			}

			prev->next = b->next;
			destroy_entity(&b);
			b = prev;
		}
		prev = b;
	}
}

void render_bullets()
{
	Entity* b;

	for (b = bullet_head->next; b != NULL; b = b->next) {
		draw_entity(b);
		draw_rect(get_entity_rect(b));
		//draw_vector(get_entity_center(b), add_vec(b->pos, b->vel));
	}
}

void check_bullet_collision(Entity* b)
{
	Entity* e;

	if (b->side == PLAYER_SIDE) {
		for (e = enemy_head->next; e != NULL; e = e->next)
		{
			if (check_entity_collision(b, e))
			{
				b->health = 0;
				e->health = 0;
				score++;
			}
		}
	}
	else if ((b->side == ENEMY_SIDE) && player) {
		if (check_entity_collision(b, player))
		{
			b->health = 0;
			//player->health -= 1;
		}
	}
}