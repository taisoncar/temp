#include "player.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "entity.h"
#include "setup.h"
#include "input.h"
#include "projectile.h"
#include "animator.h"

#define PLAYER_SPEED 400.0f
#define PLAYER_HEALTH 10
#define PLAYER_RELOAD 10

Player* player = NULL;

void kill_player();

void spawn_player()
{
    player = malloc(sizeof(Player));
    if (player == NULL) {
        printf("Insufficient memory");
        exit(1);
    }
    player->entity = create_entity();

    //Setup player animator and anim_list
    player->anim_list = malloc(PLAYER_TOTAL_ANIM * sizeof(Animation));
    player->anim_list[PLAYER_IDLE] = create_animation("../res/img/PlayerIdle.png", 10.0f);
    player->anim_list[PLAYER_WALK] = create_animation("../res/img/PlayerJump.png", 10.0f);
    player->anim_list[PLAYER_JUMP] = create_animation("../res/img/PlayerJump.png", 10.0f);
    start_animation(&player->animator, player->anim_list[PLAYER_WALK]);

    //Setup player entity
    player->entity->w = player->anim_list->wh * 3;
    player->entity->h = player->anim_list->wh * 3;

    player->entity->pos.x = (SCREEN_WIDTH / 2) - (player->entity->w / 2); 
    player->entity->pos.y = SCREEN_HEIGHT - player->entity->h;

    player->entity->vel.x = 0.0f;
    player->entity->vel.y = 0.0f;
    player->entity->speed = PLAYER_SPEED;

    player->entity->health = PLAYER_HEALTH;
    player->entity->side = PLAYER_SIDE;
    player->entity->countdown = 0;

    
}

void update_player(float delta_time)
{
    if (is_fire && player && (player->entity->countdown-- <= 0)) {
		spawn_bullet(player->entity);
		player->entity->countdown = PLAYER_RELOAD;
	}

    if (player && (player->entity->health <= 0)) {
        kill_player();
    }
    else if (player) {
        update_entity(player->entity, delta_time);

        //If out of bound
        if (player->entity->pos.x < 0) {
            player->entity->pos.x = 0;
        }
        else if (player->entity->pos.x + player->entity->w > SCREEN_WIDTH) {
            player->entity->pos.x = SCREEN_WIDTH - player->entity->w;
        }
        if (player->entity->pos.y < 0) {
            player->entity->pos.y = 0;
        }
        else if (player->entity->pos.y + player->entity->h > SCREEN_HEIGHT) {
            player->entity->pos.y = SCREEN_HEIGHT - player->entity->h;
        }
    }
}

void draw_player()
{
    if (player) {
        /* draw_entity(player); */

        SDL_Color green = {0x00, 0xFF, 0x00, 0xFF};
        draw_rect(get_entity_rect(player->entity), &green); 
        play_animation(&player->animator, get_entity_rect(player->entity));
    }
}

void kill_player()
{
    destroy_entity(&player->entity, NULL);
    free(player->anim_list);
    free(player);
    player = NULL;
    is_fire = false;
}