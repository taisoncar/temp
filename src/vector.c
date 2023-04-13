#include "vector.h"
#include <SDL.h>
#include <math.h>
#include "setup.h"

Vector2 calc_slope(Vector2 src, Vector2 dest)
{
	Vector2 slope;
	slope.x = (dest.x - src.x);
	slope.y = (dest.y - src.y);

	return slope;
}

void normalize_vec(Vector2* vector)
{
	float magnitude = sqrt(pow(vector->x, 2) + pow(vector->y, 2));
	if (magnitude && (magnitude != 1.0f)) {
		vector->x /= magnitude;
		vector->y /= magnitude;
	}
}

void scale_vec(Vector2* vector, float scale)
{
	vector->x *= scale;
	vector->y *= scale;
}

Vector2 add_vec(Vector2 p1, Vector2 p2)
{
	Vector2 p3;
	p3.x = p1.x + p2.x;
	p3.y = p1.y + p2.y;

	return p3;
}



void draw_vector(Vector2 p1, Vector2 p2)
{
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0xFF, 0xFF, 255);
	SDL_RenderDrawLine(g_renderer, p1.x, p1.y, p2.x, p2.y);
}