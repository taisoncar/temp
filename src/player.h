#pragma once

#include "entity.h"
#include "animator.h"

typedef struct {
    Animation animation;
} Player;

extern Entity* player;
extern int score;

void spawn_player();
void init_player(Entity* player);
void update_player(float delta_time);
void draw_player();
