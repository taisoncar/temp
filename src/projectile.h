#pragma once

#include <SDL.h>
#include "entity.h"
#include "util.h"

extern Entity_list bullet_list;
extern bool is_fire;

void spawn_bullet(Entity* source);
void fire_bullet(Entity* entity);
void update_bullets(float delta_time);
void draw_bullets();
void check_bullet_collision(Entity* b);