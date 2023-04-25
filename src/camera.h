#pragma once

#include <SDL.h>
#include "vector.h"

SDL_Rect world_to_screen(SDL_Rect world_pos);
SDL_Rect screen_to_world(SDL_Rect screen_pos);

void update_camera();
