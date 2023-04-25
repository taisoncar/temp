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
#include "camera.h"

#define PLAYER_SPEED 400.0f
#define PLAYER_HEALTH 100
#define PLAYER_RELOAD 10

Player* player = NULL;

void update_player_animation();
SDL_Rect get_player_hitbox();

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
    player->entity.w = player->animation_list->wh;
    player->entity.h = player->animation_list->wh;

    player->entity.pos.x = (SCREEN_WIDTH / 2) - (player->entity.w / 2); 
    player->entity.pos.y = SCREEN_HEIGHT - player->entity.h;

    player->entity.vel.x = 0.0f;
    player->entity.vel.y = 0.0f;
    player->entity.speed = PLAYER_SPEED;

    player->entity.health = PLAYER_HEALTH;
    player->entity.side = PLAYER_SIDE;
    player->reload = 0;

    //Setup player hitbox
    player->hitbox = (SDL_Rect){
        player->animator.animation.wh / 4,
        0,
        player->animator.animation.wh / 2,
        player->animator.animation.wh,
    };

    //Setup player properties
    player->is_fire = false;
    player->facing_right = true;
    player->score = 0;
}

void kill_player()
{
    free(player);
    player = NULL;
    printf("freed player\n");
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
        if (player->is_fire && (player->reload-- <= 0)) {
            spawn_bullet(player->entity);
		    player->reload = PLAYER_RELOAD;
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
        SDL_Rect src = get_animation_rect(player->animator);
        SDL_Rect dest = {
            player->entity.pos.x,
            player->entity.pos.y,
            src.w,
            src.h
        };
        SDL_Rect screen_dest = world_to_screen(dest);
        SDL_RenderCopyEx(
            g_renderer, 
            player->animator.animation.texture, 
            &src, 
            &screen_dest, 
            0, 
            NULL, 
            player->facing_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL
        );

        //Draw player display box
        SDL_Color green_color = {0x00, 0xFF, 0x00, 0xFF};
        draw_rect(screen_dest, &green_color); 

        //Draw player collision box
        SDL_Color blue_color = {0x00, 0x00, 0xFF, 0xFF};
        //draw_rect(get_player_hitbox(), &blue_color);
        draw_rect(world_to_screen(get_player_hitbox()), &blue_color);  
    }
}


SDL_Rect get_player_hitbox()
{
    SDL_Rect rect = {
        player->entity.pos.x + player->hitbox.x,
        player->entity.pos.y + player->hitbox.y,
        player->hitbox.w,
        player->hitbox.h
    };

    return rect;
}
