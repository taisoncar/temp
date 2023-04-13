#pragma once

#include <SDL.h>
#include "util.h"

typedef enum {
	PLAYER_SIDE,
	ENEMY_SIDE
} Side;

typedef struct Entity {
	SDL_Texture*	texture;

	int				w, h;
	Vector2			pos;
	Vector2			vel;	
	float			speed;

	int				health;
	Side			side;
	int				countdown;
	struct Entity*	next;
} Entity;

typedef struct {
	Entity* head;
	Entity* tail;
} Entity_list;

Entity* create_entity(SDL_Texture* texture, int x, int y, float speed, int health, Side side);
void destroy_entity(Entity** entity);
void update_entity(Entity* entity, double delta_time);
void draw_entity(Entity* entity);
SDL_Rect get_entity_rect(Entity* entity);
bool check_entity_collision(Entity* e1, Entity* e2);
Vector2 get_entity_center(Entity* entity);
void print_entity(Entity* entity);

