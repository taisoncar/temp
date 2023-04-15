#pragma once

#include <SDL.h>

typedef struct {
    SDL_Texture* texture;
    int         wh;
    int         frame_count;
    int         frame_index;
    float       frame_interval;
    float       frame_timer;
} Animation;

Animation create_animation(char *path, float frame_interval);
void play_animation(Animation *animation, SDL_Rect dest);
