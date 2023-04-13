#pragma once

#include "entity.h"

#define PLAYER_RELOAD 10

extern Entity* player;
extern int score;

void create_player();
void update_player(double delta_time);
