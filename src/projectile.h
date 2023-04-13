#pragma once

#include <SDL.h>
#include "entity.h"
#include "util.h"

extern Entity* bullet_head;
extern Entity* bullet_tail;
extern bool is_fire;

void init_bullet();
void fire_bullet(Entity* entity);
void update_bullets(double delta_time);
void render_bullets();
void check_bullet_collision(Entity* b);

