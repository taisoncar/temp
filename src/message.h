#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

enum Message_list {
	M_FPS,
	M_SCORE,
	M_HEALTH,
	M_TOTAL
};

typedef struct {
	char			text[100];
	TTF_Font*		font;
	SDL_Color		color;
	SDL_Rect		rect;
	SDL_Texture*	texture;
} Message;

extern Message* g_message[M_TOTAL];

Message* create_message(TTF_Font* font, char* text, SDL_Color* text_color, int x, int y);
void init_messages();
void destroy_messages();
void update_messages();
void draw_messages();

