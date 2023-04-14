#pragma once

#include <SDL.h>
#include "vector.h"

#define MAX_FPS 60.0f
#define TARGET_FRAME_TIME 1000.0f / MAX_FPS

typedef enum {
	false,
	true
} bool;

extern float average_fps;
extern Uint64 frame_time;

int rand_range(int min, int max);
bool collision(SDL_Rect rect1, SDL_Rect rect2);
Vector2 get_rect_center(SDL_Rect rect);
void draw_rect(SDL_Rect rect, SDL_Color* rect_color);

void calc_fps();
void limit_fps();