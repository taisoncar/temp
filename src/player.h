#pragma once

#include "entity.h"

#define PLAYER_RELOAD 10

extern Entity* player;
extern int score;

void spawn_player();
void init_player(Entity* player);
void update_player(float delta_time);
void draw_player();
/* void update_player(double delta_time);
void draw_player(); */
