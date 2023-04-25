#pragma once

#include <SDL.h>
#include "entity.h"
#include "animator.h"

enum Player_anim {
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_JUMP,
    TOTAL_PLAYER_ANIM
};

typedef struct {
    Entity      entity;
    bool        is_fire;
    bool        facing_right;
    int         score;
    int         reload;

    Animator    animator;
    Animation   animation_list[TOTAL_PLAYER_ANIM];

    SDL_Rect    hitbox;       
} Player;

extern Player* player;

void spawn_player();
void kill_player();
void update_player(float delta_time);
void draw_player();
