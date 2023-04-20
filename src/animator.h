#pragma once

#include <SDL.h>

typedef struct {
    SDL_Texture     *texture;
    int             wh;
    int             frame_count;
    float           frame_interval;
} Animation;

typedef struct {
    Animation       animation;
    int             frame_index;
    float           timer;
} Animator;

Animation create_animation(char *path, float frame_interval);
void start_animation(Animator *animator, Animation animation);
void update_animator(Animator *animator, float delta_time);
SDL_Rect play_animation(Animator animator);
