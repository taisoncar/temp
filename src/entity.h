#pragma once

#include <SDL.h>
#include "util.h"
#include "animator.h"

/* typedef enum {
	PLAYER_ID,
	ENEMY_ID,
	BULLET_ID
} Entity_ID; */

typedef enum {
	PLAYER_SIDE,
	ENEMY_SIDE
} Side;

typedef void (*Extension);

struct Entity;
typedef struct Entity Entity;
struct Entity {
	int			w, h;
	Vector2 	pos;
	Vector2		vel;	
	float		speed;

	int			health;
	Side		side;
};

void update_entity(Entity* entity, float delta_time);

//Utilities
SDL_Rect get_entity_rect(Entity entity);
Vector2 get_entity_center(Entity entity);
bool check_entity_collision(Entity e1, Entity e2);
