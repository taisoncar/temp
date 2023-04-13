#include "player.h"
#include "entity.h"
#include "setup.h"
#include "input.h"

#define PLAYER_SPEED 400.0f

Entity* player = NULL;

void kill_player();

void create_player()
{
    player = create_entity(g_texture[T_PLAYER], 0, 0, PLAYER_SPEED, 5, PLAYER_SIDE);
    player->w /= 2;
    player->h /= 2;
    player->pos.x = (SCREEN_WIDTH / 2) - (player->w / 2); 
    player->pos.y = SCREEN_HEIGHT - player->h;
}

void update_player(double delta_time)
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

void kill_player()
{
    destroy_entity(&player);
    is_fire = false;
}