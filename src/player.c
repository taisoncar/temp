#include "player.h"
#include <SDL.h>
#include "entity.h"
#include "setup.h"
#include "input.h"

#define PLAYER_SPEED 400.0f
#define PLAYER_HEALTH 10

Entity* player = NULL;

void kill_player();

void spawn_player()
{
    player = create_entity();
    init_player(player);
}

void init_player(Entity* new_player)
{
    new_player->texture = g_texture[T_PLAYER];
    SDL_QueryTexture(new_player->texture, NULL, NULL, &new_player->w, &new_player->h);

    new_player->w /= 2;
    new_player->h /= 2;
    new_player->pos.x = (SCREEN_WIDTH / 2) - (new_player->w / 2); 
    new_player->pos.y = SCREEN_HEIGHT - new_player->h;
    new_player->vel.x = 0.0f;
    new_player->vel.y = 0.0f;
    new_player->speed = PLAYER_SPEED;

    new_player->health = PLAYER_HEALTH;
    new_player->side = PLAYER_SIDE;
    new_player->countdown = 0;
}

void update_player(float delta_time)
{
    if (player && (player->health <= 0)) {
        kill_player();
    }
    else if (player) {
        update_entity(player, delta_time);

        //If out of bound
        if ((player->pos.x < 0) || (player->pos.x + player->w > SCREEN_WIDTH)) {
            player->pos.x = 0;
        }
        if ((player->pos.y < 0) || (player->pos.y + player->h > SCREEN_HEIGHT)) {
            player->pos.y = 0;
        }
    }
}

void draw_player()
{
    draw_entity(player);
    SDL_Color green = {0x00, 0xFF, 0x00, 0xFF};
    draw_rect(get_entity_rect(player), &green);
}

void kill_player()
{
    remove_entity(&player, NULL);
    is_fire = false;
}