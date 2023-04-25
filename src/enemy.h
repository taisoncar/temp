#pragma once

#include <SDL.h>
#include "entity.h"
#include "animator.h"

enum Enemy_anim {
    ENEMY_WALK,
    ENEMY_DIE,
    TOTAL_ENEMY_ANIM
};

struct Enemy;
typedef struct Enemy Enemy;
struct Enemy{
    Entity entity;
    int reload;

    Animator    animator;
    Animation   animation_list[TOTAL_ENEMY_ANIM];

    Enemy *next;
};

typedef struct {
    Enemy head;
    Enemy *tail;
} Enemy_list;

extern Enemy_list enemy_list;

void init_enemy_list();
void destroy_enemy_list();
void spawn_enemy();

void update_enemies(float delta_time);
void draw_enemies();