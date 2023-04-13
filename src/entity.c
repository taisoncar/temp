#include "entity.h"
#include <stdio.h>
#include <SDL.h>
#include "setup.h"
#include "player.h"

Entity* create_entity(SDL_Texture* texture, int x, int y, float speed, int health, Side side)
{
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if (entity == NULL) {
        printf("Insufficient memory");
        exit(1);
    }

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    *entity = (Entity){
        texture,
        w, h,
        { (float)x, (float)y }, //pos
        { 0.0f, 0.0f },         //vel
        speed,
        health,
        side,
        0,                      //countdown
        NULL                    //next
    };

    return entity;
}

void destroy_entity(Entity** entity)
{
    free(*entity);
    *entity = NULL;
}

void update_entity(Entity* entity, double delta_time)
{
    if (entity) {
        Vector2 scaled_vel = entity->vel;
        normalize_vec(&scaled_vel);
        scale_vec(&scaled_vel, entity->speed);

        entity->pos.x += scaled_vel.x * delta_time;
        entity->pos.y += scaled_vel.y * delta_time;
    }
}

void draw_entity(Entity* entity)
{
	if (entity) {
		SDL_Rect entity_rect = get_entity_rect(entity);
		SDL_RenderCopy(g_renderer, entity->texture, NULL, &entity_rect);
	}
}

SDL_Rect get_entity_rect(Entity* entity)
{
    SDL_Rect entity_rect;
    entity_rect.x = entity->pos.x;
    entity_rect.y = entity->pos.y;
    entity_rect.w = entity->w;
    entity_rect.h = entity->h;

    return entity_rect;
}

Vector2 get_entity_center(Entity* entity)
{
    return get_rect_center(get_entity_rect(entity));
}

bool check_entity_collision(Entity* e1, Entity* e2)
{
    return collision(get_entity_rect(e1), get_entity_rect(e2));
}

void print_entity(Entity* entity)
{
    static int cooldown = 0;
    if (cooldown-- <= 0) {
        printf("Entity side: %d\n", entity->side);
        printf("Entity pos: %f, %f\n", entity->pos.x, entity->pos.y);
        printf("Entity vel: %f, %f\n\n", entity->vel.x, entity->vel.y);

        cooldown = 60;
    }
}

Entity_list create_entity_list()
{
    Entity_list entity_list;

    entity_list.head = (Entity*)malloc(sizeof(Entity));
    if (!entity_list.head) {
        printf("Insufficient memory");
		exit(1);
    }

    entity_list.head->next = NULL;
    entity_list.tail = entity_list.head;

    return entity_list;
}

void add_entity_to_list(Entity_list* entity_list, Entity* new_entity)
{
    entity_list->tail->next = new_entity;
    entity_list->tail = new_entity;
}

void remove_entity_from_list(Entity_list* entity_list, Entity** current, Entity** prev)
{
    if (*current == entity_list->tail) {
       entity_list->tail = *prev;
    }

    (*prev)->next = (*current)->next;
    destroy_entity(current);
    *current = *prev;
}

void draw_entity_list(Entity_list entity_list)
{
	for (Entity* current = entity_list.head->next; current != NULL; current = current->next) {
		draw_entity(current);
		draw_rect(get_entity_rect(current));
	}
}

void destroy_entity_list(Entity_list* entity_list)
{
    Entity* prev = entity_list->head;
    for (Entity* current = entity_list->head->next; current != NULL; current = current->next) {
        remove_entity_from_list(entity_list, &current, &prev);
        prev = current;
    }
}