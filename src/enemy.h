#pragma once

#include <SDL.h>
#include "entity.h"

extern Entity* enemy_head;
extern Entity* enemy_tail;

void init_enemy();
void update_enemies(double delta_time);
void render_enemies();