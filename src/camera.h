#pragma once

#include <SDL.h>
#include "vector.h"

extern float scale;

SDL_Rect world_to_screen(Vector2 world_pos, int w, int h);
SDL_Rect screen_to_world(SDL_Rect screen_pos);

void update_camera();
