#pragma once

#include <SDL.h>
#include "util.h"
#include "animator.h"

typedef enum {
	PLAYER_ID,
	ENEMY_ID,
	BULLET_ID
} Entity_ID;

typedef enum {
	PLAYER_SIDE,
	ENEMY_SIDE
} Side;

typedef void (*Extension);

struct Entity;
typedef struct Entity Entity;
struct Entity {
	Entity_ID 	id;

	SDL_Texture* 	texture;

	int			w, h;
	Vector2 	pos;
	Vector2		vel;	
	float		speed;

	int			health;
	Side		side;
	int			countdown;

	//Entity specific properties
	union {
		bool 	is_fire;
	};

	Entity*		prev;
	Entity*		next;
};

typedef struct {
	Entity* head;
	Entity* tail;
} Entity_list;

Entity* create_entity();
void update_entity(Entity* entity, double delta_time);
void draw_entity(Entity* entity);

Entity_list create_entity_list();
void add_entity_to_list(Entity *entity, Entity_list *e_list);
void destroy_entity(Entity **entity, Entity_list *e_list);
void destroy_entity_list(Entity_list *e_list);

SDL_Rect get_entity_rect(Entity* entity);
Vector2 get_entity_center(Entity* entity);
bool check_entity_collision(Entity* e1, Entity* e2);
