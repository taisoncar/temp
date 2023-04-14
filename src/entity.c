#include "entity.h"
#include <stdio.h>
#include <SDL.h>
#include "setup.h"
#include "player.h"
#include "enemy.h"

Entity* create_entity()
{
    Entity* new_entity = (Entity*)malloc(sizeof(Entity));
    if (new_entity == NULL) {
        printf("Insufficient memory");
        exit(1);
    }
    new_entity->prev = NULL;
    new_entity->next = NULL;

    return new_entity;
}

void update_entity(Entity* entity, double delta_time)
{
    Vector2 scaled_vel = entity->vel;
    normalize_vec(&scaled_vel);
    scale_vec(&scaled_vel, entity->speed);

    entity->pos.x += scaled_vel.x * delta_time;
    entity->pos.y += scaled_vel.y * delta_time;

    //TODO: move health check to here if no dependency
} 

void draw_entity(Entity* entity)
{
    SDL_Rect entity_rect = get_entity_rect(entity);
    SDL_RenderCopy(g_renderer, entity->texture, NULL, &entity_rect);
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
    entity_list.head->prev = NULL;
    entity_list.tail = entity_list.head;

    return entity_list;
}

void add_entity_to_list(Entity* entity, Entity_list* e_list)
{
    entity->prev = e_list->tail;
    e_list->tail->next = entity;
    e_list->tail = entity;
}

void remove_entity(Entity** entity, Entity_list* e_list)
{
    if (e_list) {
        /* printf("removing: %p\n", *entity);
        printf("next: %p\n", (*entity)->next);
        printf("prev: %p\n\n", (*entity)->prev); */

        if (*entity == e_list->tail) {
            e_list->tail = (*entity)->prev;
        }
        else {
            //Link next node to prev node
            (*entity)->next->prev = (*entity)->prev;
        }

        //Keep a reference to prev node
        Entity* prev = (*entity)->prev;

        //Link prev node to next node
        (*entity)->prev->next = (*entity)->next;

        free(*entity);
        *entity = prev;
    }
    else {
        //If entity is not part of a list
        free(*entity);
        *entity = NULL;
    }
}

/*Entity utils*/
//////////////////////////////////////////////////

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

/////////////////////////////////////////////////