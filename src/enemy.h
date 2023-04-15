#pragma once

#include <SDL.h>
#include "entity.h"

extern Entity_list enemy_list;

void spawn_enemy();
void update_enemies(double delta_time);
void draw_enemies();