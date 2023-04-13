#include "projectile.h"
#include <stdio.h>
#include "entity.h"
#include "player.h"
#include "setup.h"
#include "enemy.h"
#include "util.h"

#define BULLET_SPEED 500.0f

Entity_list bullet_list;
int score = 0;

void init_bullet()
{
	bullet_list = create_entity_list();
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
	}

	add_entity_to_list(&bullet_list, new_bullet);
}

void update_bullets(double delta_time)
{
	if (is_fire && player && (player->countdown-- <= 0)) {
		fire_bullet(player);
		player->countdown = PLAYER_RELOAD;
	}
	Entity* current;
	Entity* prev;

	prev = bullet_list.head;

	for (current = bullet_list.head->next; current != NULL; current = current->next) {
		update_entity(current, delta_time);
		check_bullet_collision(current);

		if ( (current->pos.y < 0) || (current->health == 0) || (current->countdown-- <= 0) ){
			remove_entity_from_list(&bullet_list, &current, &prev);
		}
		prev = current;
	}
}

void render_bullets()
{
	Entity* b;

	for (b = bullet_list.head->next; b != NULL; b = b->next) {
		draw_entity(b);
		draw_rect(get_entity_rect(b));
	}
}

void check_bullet_collision(Entity* b)
{
	if (b->side == PLAYER_SIDE) {
		for (Entity* e = enemy_list.head->next; e != NULL; e = e->next)
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
			player->health += 1;
		}
	}
}