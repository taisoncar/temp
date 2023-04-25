#include "camera.h"
#include <SDL.h>
#include <stdio.h>
#include "setup.h"
#include "vector.h"
#include "player.h"

Vector2 offset = { 0.0f, 0.0f };
float scale = 1.0f;

SDL_Rect world_to_screen(SDL_Rect world_pos)
{
    SDL_Rect screen_pos;
    screen_pos.x = (world_pos.x - offset.x) * scale;
    screen_pos.y = (world_pos.y - offset.y) * scale;
    screen_pos.w = world_pos.w * scale;
    screen_pos.h = world_pos.h * scale;

    return screen_pos;
}

Vector2 world_to_screen_vec(Vector2 world_pos)
{
    Vector2 screen_pos;
    screen_pos.x = (world_pos.x - offset.x) * scale;
    screen_pos.y = (world_pos.y - offset.y) * scale;

    return screen_pos;
}

SDL_Rect screen_to_world(SDL_Rect screen_pos)
{
    SDL_Rect world_pos;
    world_pos.x = screen_pos.x / scale + offset.x;
    world_pos.y = screen_pos.y / scale + offset.y;
    world_pos.w = screen_pos.w / scale;
    world_pos.h = screen_pos.h / scale;

    return world_pos;
}

void update_camera()
{
    if (player) {
        Vector2 center;
        center.x = SCREEN_WIDTH / 2;
        center.y = SCREEN_HEIGHT / 2;
        offset = calc_slope(center, player->entity.pos);
    }
    printf("offset x: %f\n", offset.x);
    printf("offset y: %f\n\n", offset.y);
}
