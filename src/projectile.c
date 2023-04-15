#include "projectile.h"
#include <stdio.h>
#include "entity.h"
#include "player.h"
#include "setup.h"
#include "enemy.h"
#include "util.h"

#define BULLET_SPEED 500.0f
#define BULLET_DURATION 600
#define BULLET_HEALTH 1

Entity_list bullet_list;
int score = 0;

void init_bullet(Entity* bullet, Entity* source);

void spawn_bullet(Entity* source)
{
	Entity* new_bullet = create_entity();
	init_bullet(new_bullet, source);
	add_entity_to_list(new_bullet, &bullet_list);
}

void init_bullet(Entity* bullet, Entity* source)
{
    bullet->texture = g_texture[T_BULLET];
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->w = 5;
    bullet->h = 5;
    bullet->pos.x = source->pos.x + (source->w / 2) - (bullet->w / 2);
    bullet->pos.y = source->pos.y;
    bullet->vel.x = 0.0f;
	if (source->side == PLAYER_SIDE) {
		bullet->vel.y = -1.0f;
	}
	else if (source->side == ENEMY_SIDE) {
		bullet->pos.y += source->h;
		bullet->vel = calc_slope(get_entity_center(bullet), get_entity_center(player->entity));
	}
    bullet->speed = BULLET_SPEED;

    bullet->health = BULLET_HEALTH;
    bullet->side = source->side;
    bullet->countdown = BULLET_DURATION;
}

void update_bullets(float delta_time)
{
	for (Entity* i = bullet_list.head->next; i != NULL; i = i->next) {
		update_entity(i, delta_time);
		check_bullet_collision(i);

		if ( (i->pos.y < 0) || (i->health == 0) || (i->countdown-- <= 0) ){
			destroy_entity(&i, &bullet_list);
		}
	}
}

void draw_bullets()
{
	for (Entity* i = bullet_list.head->next; i != NULL; i = i->next) {
		draw_entity(i);
		if (i->side == PLAYER_SIDE) {
			SDL_Color green = {0x00, 0xFF, 0x00, 0xFF};
			draw_rect(get_entity_rect(i), &green);
		}
		else if (i->side == ENEMY_SIDE) {
			SDL_Color blue = {0x00, 0x00, 0xFF, 0xFF};
			draw_rect(get_entity_rect(i), &blue);
		}
	}
}

void check_bullet_collision(Entity* bullet)
{
	if (bullet->side == PLAYER_SIDE) {
		for (Entity* e = enemy_list.head->next; e != NULL; e = e->next)
		{
			if (check_entity_collision(bullet, e))
			{
				bullet->health -= 1;
				e->health -= 1;
				score++;
			}
		}
	}
	else if ((bullet->side == ENEMY_SIDE) && player) {
		if (check_entity_collision(bullet, player->entity))
		{
			bullet->health -= 1;
			player->entity->health -= 1;
		}
	}
}