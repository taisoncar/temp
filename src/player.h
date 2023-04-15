#pragma once

#include "entity.h"
#include "animator.h"

enum Player_animation {
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_JUMP,
    PLAYER_TOTAL_ANIM
};

typedef struct {
    Entity* entity;
    Animator animator;
    Animation* anim_list;
} Player;

extern Player* player;
extern int score;

void spawn_player();
void init_player(Entity* player);
void update_player(float delta_time);
void draw_player();
