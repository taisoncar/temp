#include "projectile.h"
#include <stdio.h>
#include <assert.h>
#include "entity.h"
#include "player.h"
#include "setup.h"
#include "enemy.h"
#include "util.h"
#include "camera.h"

#define BULLET_SPEED 500.0f
#define BULLET_DURATION 600	//unused
#define BULLET_HEALTH 1

Bullet_list bullet_list;

void init_bullet_list()
{
    bullet_list.head.next = NULL;
    bullet_list.tail = &bullet_list.head;
}

void destroy_bullet_list()
{
	Bullet *prev = &bullet_list.head;
	for (Bullet *i = bullet_list.head.next; i != NULL; i = i->next) {
		if (i == bullet_list.tail) {
			bullet_list.tail = prev;
		}
		prev->next = i->next;
		free(i);
		i = prev;
	}
}

void spawn_bullet(Entity source)
{
	Bullet *new_bullet = malloc(sizeof(Bullet));
	assert(new_bullet);

	bullet_list.tail = bullet_list.tail->next = new_bullet;
	new_bullet->next = NULL;

	//Setup bullet entity struct
	new_bullet->texture = g_texture[T_BULLET];
    SDL_QueryTexture(new_bullet->texture, NULL, NULL, &new_bullet->entity.w, &new_bullet->entity.h);

    //new_bullet->entity.w = 5;
    //new_bullet->entity.h = 5;
    new_bullet->entity.pos.x = source.pos.x + (source.w / 2) - (new_bullet->entity.w / 2);
    new_bullet->entity.pos.y = source.pos.y;
    new_bullet->entity.vel.x = 0.0f;
	if (source.side == PLAYER_SIDE) {
		new_bullet->entity.vel.y = -1.0f;
	}
	else if (source.side == ENEMY_SIDE) {
		new_bullet->entity.pos.y += source.h;
		new_bullet->entity.vel = calc_slope(get_entity_center(new_bullet->entity), get_entity_center(player->entity));
	}
    new_bullet->entity.speed = BULLET_SPEED;

    new_bullet->entity.health = BULLET_HEALTH;
    new_bullet->entity.side = source.side;
}

void update_bullets(float delta_time)
{
	Bullet *prev = &bullet_list.head;
	for (Bullet *i = bullet_list.head.next; i != NULL; i = i->next) {
		update_entity(&i->entity, delta_time);
		check_bullet_collision(&i->entity);

		if ( (i->entity.pos.y < 0) || (i->entity.health <= 0) ){
			if (i == bullet_list.tail) {
				bullet_list.tail = prev;
			}
			prev->next = i->next;
			free(i);
			i = prev;
		}
		prev = i;
	}
}

void draw_bullets()
{
	for (Bullet *i = bullet_list.head.next; i != NULL; i = i->next) {
		SDL_Rect entity_rect = get_entity_rect(i->entity);
		//entity_rect = world_to_screen(entity_rect);
    	SDL_RenderCopy(g_renderer, i->texture, NULL, &entity_rect);

		if (i->entity.side == PLAYER_SIDE) {
			SDL_Color green = {0x00, 0xFF, 0x00, 0xFF};
			//draw_rect(get_entity_rect(i->entity), &green);
			//draw_rect(world_to_screen(get_entity_rect(i->entity)), &green);
		}
		else if (i->entity.side == ENEMY_SIDE) {
			SDL_Color blue = {0xFC, 0x29, 0x47, 0xFF};
			//draw_rect(get_entity_rect(i->entity), &blue);
			//draw_rect(world_to_screen(get_entity_rect(i->entity)), &blue);
		}
	}
}

void check_bullet_collision(Entity* bullet)
{
	if (bullet->side == PLAYER_SIDE) {
		for (Enemy *e = enemy_list.head.next; e != NULL; e = e->next)
		{
			if (check_entity_collision(*bullet, e->entity))
			{
				bullet->health -= 1;
				e->entity.health -= 1;
				if (player) {
					player->score++;
				}
			}
		}
	}
	else if ((bullet->side == ENEMY_SIDE) && player) {
		if (check_entity_collision(*bullet, player->entity))
		{
			bullet->health -= 1;
			player->entity.health -= 1;
		}
	}
}