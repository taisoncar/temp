#pragma once

#include <SDL.h>
#include "entity.h"

extern Entity_list enemy_list;

void init_enemy();
void update_enemies(double delta_time);
void render_enemies();