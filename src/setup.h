#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 1000

enum Texture_list {
	T_PLAYER,
	T_BULLET,
	T_ENEMY,
	T_TOTAL
};

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern TTF_Font* g_font;
extern SDL_Texture* g_texture[T_TOTAL];

void init_SDL();
void close_SDL();
void init_texture();
void load_font();