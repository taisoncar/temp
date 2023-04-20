#pragma once

#include <SDL.h>
#include "entity.h"

struct Enemy;
typedef struct Enemy Enemy;
struct Enemy{
    Entity entity;
    Enemy *next;
};

typedef struct {
    Enemy head;
    Enemy *tail;
} Enemy_list;

extern Enemy_list enemy_list;

void init_enemy_list();
void spawn_enemy();

void update_enemies(float delta_time);
void draw_enemies();