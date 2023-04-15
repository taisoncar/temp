#pragma once

typedef struct {
	float x;
	float y;
} Vector2;

Vector2 calc_slope(Vector2 src, Vector2 dest);
Vector2 normalize_vec(Vector2 vector);
Vector2 scale_vec(Vector2 vector, float scalar);
Vector2 add_vec(Vector2 p1, Vector2 p2);
void draw_vector(Vector2 p1, Vector2 p2);