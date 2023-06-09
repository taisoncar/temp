#include "util.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "entity.h"
#include "setup.h"
#include "vector.h"

#define TOTAL_SAMPLES 100

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

float average_fps = 0.0f;
Uint64 frame_time = 0;

int rand_range(int min, int max)
{
	return min + rand() % (max - min + 1);
}

bool rect_collision(SDL_Rect rect1, SDL_Rect rect2)
{
	return (MAX(rect1.x, rect2.x) < MIN(rect1.x + rect1.w, rect2.x + rect2.w)) && (MAX(rect1.y, rect2.y) < MIN(rect1.y + rect1.h, rect2.y + rect2.h));
}

Vector2 get_rect_center(SDL_Rect rect)
{
	Vector2 center;
	center.x = rect.x + (rect.w / 2);
	center.y = rect.y + (rect.h / 2);

	return center;
}

void draw_rect(SDL_Rect rect, SDL_Color* color)
{
	if (!color) {
		*color = (SDL_Color){0xFF, 0xFF, 0xFF, 0xFF};
	}
	SDL_SetRenderDrawColor(g_renderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawRect(g_renderer, &rect);
}

void calc_fps()
{
	static Uint64 frame_times[TOTAL_SAMPLES];

	static Uint64 prev_ticks = 0;
	static Uint64 current_frame = 0;

	frame_time = SDL_GetTicks64() - prev_ticks;
	frame_times[current_frame % TOTAL_SAMPLES] = frame_time;

	int frame_count;
	if (++current_frame < TOTAL_SAMPLES) {
		frame_count = current_frame;
	}
	else {
		frame_count = TOTAL_SAMPLES;
	}

	float average_frame_time = 0;
	for (int i = 0; i < frame_count; i++) {
		average_frame_time += frame_times[i];
	}
	average_frame_time /= frame_count;

	if (average_frame_time > 0) {
		average_fps = 1000.0f / average_frame_time;
	}
	prev_ticks = SDL_GetTicks64();
}

void limit_fps()
{
	static Uint64 prev_ticks = 0;
	Uint64 frame_ticks = SDL_GetTicks64() - prev_ticks;

	if (frame_ticks < TARGET_FRAME_TIME) {
		SDL_Delay(TARGET_FRAME_TIME - frame_ticks);
	}
	prev_ticks = SDL_GetTicks64();
}

