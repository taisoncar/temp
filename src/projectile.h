#pragma once

#include <SDL.h>
#include "entity.h"

struct Bullet;
typedef struct Bullet Bullet;
struct Bullet{
    Entity entity;
    Bullet *next;
};

typedef struct {
    Bullet head;
    Bullet *tail;
} Bullet_list;

extern Bullet_list bullet_list;

void init_bullet_list();
void destroy_bullet_list();
void spawn_bullet(Entity source);

void update_bullets(float delta_time);
void draw_bullets();

void check_bullet_collision(Entity* b);