#pragma once

#include <SDL.h>
#include "util.h"

typedef enum {
	PLAYER_ID,
	ENEMY_ID,
	BULLET_ID
} Entity_ID;

typedef enum {
	PLAYER_SIDE,
	ENEMY_SIDE
} Side;

struct Entity;
typedef struct Entity Entity;

typedef void (*Update_f)(Entity*, double);
typedef void (*Draw_f)(Entity*);

struct Entity {
	Entity_ID		id;
	SDL_Texture*	texture;

	int				w, h;
	Vector2			pos;
	Vector2			vel;	
	float			speed;

	int				health;
	Side			side;
	int				countdown;
	struct Entity*	prev;
	struct Entity*	next;

	/* Update_f 		update;
	Draw_f 			draw; */
};

typedef struct {
	Entity* head;
	Entity* tail;
} Entity_list;

Entity *create_entity();
void spawn_entity(Entity_ID id);
void destroy_entity(Entity** entity);

void update_entity(Entity* entity, double delta_time);
void draw_entity(Entity* entity);

Entity_list create_entity_list();
void add_entity_to_list(Entity *entity, Entity_list *e_list);
void remove_entity(Entity **entity, Entity_list *e_list);

SDL_Rect get_entity_rect(Entity* entity);
Vector2 get_entity_center(Entity* entity);
bool check_entity_collision(Entity* e1, Entity* e2);


/* void add_entity_to_list(Entity_list *entity_list, Entity *new_entity);
void remove_entity_from_list(Entity_list *entity_list, Entity **current, Entity **prev);
void draw_entity_list(Entity_list entity_list);
void destroy_entity_list(Entity_list *entity_list); */
