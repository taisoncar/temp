#include "player.h"
#include <SDL.h>
#include "entity.h"
#include "setup.h"
#include "input.h"
#include "projectile.h"
#include "animator.h"

#define PLAYER_SPEED 400.0f
#define PLAYER_HEALTH 1000
#define PLAYER_RELOAD 10

Entity* player = NULL;

void kill_player();

void spawn_player()
{
    player = create_entity();
    init_player(player);
}

void init_player(Entity* new_player)
{
    new_player->vel.x = 0.0f;
    new_player->vel.y = 0.0f;
    new_player->speed = PLAYER_SPEED;

    new_player->health = PLAYER_HEALTH;
    new_player->side = PLAYER_SIDE;
    new_player->countdown = 0;

    Player* player_data = malloc(sizeof(Player));
    player_data->animation = create_animation("../res/img/PlayerIdle.png", 10.0f);
    new_player->data = player_data;

    new_player->w = player_data->animation.wh * 3;
    new_player->h = player_data->animation.wh * 3;

    new_player->pos.x = (SCREEN_WIDTH / 2) - (new_player->w / 2); 
    new_player->pos.y = SCREEN_HEIGHT - new_player->h;
}

void update_player(float delta_time)
{
    if (is_fire && player && (player->countdown-- <= 0)) {
		spawn_bullet(player);
		player->countdown = PLAYER_RELOAD;
	}

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
    if (player) {
        /* draw_entity(player); */
        SDL_Color green = {0x00, 0xFF, 0x00, 0xFF};
        draw_rect(get_entity_rect(player), &green); 
        Player* player_d = (Player*)player->data;
        play_animation(&player_d->animation, get_entity_rect(player));
    }
}

void kill_player()
{
    destroy_entity(&player, NULL);
    is_fire = false;
}