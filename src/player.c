#include "player.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "entity.h"
#include "setup.h"
#include "input.h"
#include "projectile.h"
#include "animator.h"

#define PLAYER_SPEED 400.0f
#define PLAYER_HEALTH 100
#define PLAYER_RELOAD 10

Player* player = NULL;

void kill_player();
void update_player_animation();

void spawn_player()
{
    player = malloc(sizeof(Player));
    assert(player);

    //Setup animator and animation_list
    player->animation_list[PLAYER_IDLE] = create_animation("../res/img/PlayerIdle.png", 0.1f);
    player->animation_list[PLAYER_WALK] = create_animation("../res/img/PlayerWalk.png", 0.1f);
    //player->animation_list[PLAYER_JUMP] = create_animation("../res/img/PlayerJump.png", 0.2f);
    start_animation(&player->animator, player->animation_list[PLAYER_IDLE]);

    //Setup player entity struct
    player->entity.w = player->animation_list->wh * 3;
    player->entity.h = player->animation_list->wh * 3;

    player->entity.pos.x = (SCREEN_WIDTH / 2) - (player->entity.w / 2); 
    player->entity.pos.y = SCREEN_HEIGHT - player->entity.h;

    player->entity.vel.x = 0.0f;
    player->entity.vel.y = 0.0f;
    player->entity.speed = PLAYER_SPEED;

    player->entity.health = PLAYER_HEALTH;
    player->entity.side = PLAYER_SIDE;
    player->entity.countdown = 0;

    //Setup player properties
    player->is_fire = false;
    player->facing_right = true;
}

void update_player(float delta_time)
{
    if (player && (player->entity.health <= 0)) {
        kill_player();
    }
    else if (player) {
        update_entity(&player->entity, delta_time);
        update_player_animation();
        update_animator(&player->animator, delta_time);

        //Check if firing bullet
        if (player->is_fire && (player->entity.countdown-- <= 0)) {
            spawn_bullet(player->entity);
		    player->entity.countdown = PLAYER_RELOAD;
        }

        //Check if out of bound
        if (player->entity.pos.x < 0) {
            player->entity.pos.x = 0;
        }
        else if (player->entity.pos.x + player->entity.w > SCREEN_WIDTH) {
            player->entity.pos.x = SCREEN_WIDTH - player->entity.w;
        }
        if (player->entity.pos.y < 0) {
            player->entity.pos.y = 0;
        }
        else if (player->entity.pos.y + player->entity.h > SCREEN_HEIGHT) {
            player->entity.pos.y = SCREEN_HEIGHT - player->entity.h;
        }
    }
}

void update_player_animation() 
{
    if (player->entity.vel.x) {
        start_animation(&player->animator, player->animation_list[PLAYER_WALK]);

        if (player->entity.vel.x > 0) {
            player->facing_right = true;
        }
        else if (player->entity.vel.x < 0) {
            player->facing_right = false;
        }
    }
    else {
        start_animation(&player->animator, player->animation_list[PLAYER_IDLE]);
    }
}


void draw_player()
{
    if (player) {
        SDL_Color green = {0x00, 0xFF, 0x00, 0xFF};
        draw_rect(get_entity_rect(player->entity), &green); 

        SDL_Rect src = play_animation(player->animator);
        SDL_Rect dest = get_entity_rect(player->entity);
        if (player->facing_right) {
            SDL_RenderCopy(g_renderer, player->animator.animation.texture, &src, &dest);
        }
        else {
            SDL_RenderCopyEx(g_renderer, player->animator.animation.texture, &src, &dest, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
}

void kill_player()
{
    free(player);
    player = NULL;
}