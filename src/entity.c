#include "entity.h"
#include <stdio.h>
#include <SDL.h>
#include "setup.h"
#include "player.h"
#include "enemy.h"

void update_entity(Entity* entity, float delta_time)
{
    Vector2 scaled_vel = scale_vec(normalize_vec(entity->vel), entity->speed);

    entity->pos.x += scaled_vel.x * delta_time;
    entity->pos.y += scaled_vel.y * delta_time;

    //TODO: move health check to here if no dependency
} 

void draw_entity(Entity entity)
{
    SDL_Rect entity_rect = get_entity_rect(entity);
    SDL_RenderCopy(g_renderer, entity.texture, NULL, &entity_rect);
}

//////////////////////////////////////////////////////////////////////
/*Entity utils*/
SDL_Rect get_entity_rect(Entity entity)
{
    SDL_Rect entity_rect;
    entity_rect.x = entity.pos.x;
    entity_rect.y = entity.pos.y;
    entity_rect.w = entity.w;
    entity_rect.h = entity.h;

    return entity_rect;
}

Vector2 get_entity_center(Entity entity)
{
    return get_rect_center(get_entity_rect(entity));
}

bool check_entity_collision(Entity e1, Entity e2)
{
    return rect_collision(get_entity_rect(e1), get_entity_rect(e2));
}
//////////////////////////////////////////////////////////////////////