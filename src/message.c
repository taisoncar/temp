#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "setup.h"
#include "player.h"
#include "util.h"

Message* g_message[M_TOTAL];

void create_texture_for_message(Message* message);
void update_message(Message* message, const char *fmt, ...);

Message* create_message(TTF_Font* font, char* text, SDL_Color* text_color, int x, int y)
{
    Message* message = (Message*)malloc(sizeof(Message));
    if (message == NULL) {
        printf("Insufficient memory");
        exit(1);
    }

    if (!text_color) {
        message->color = (SDL_Color){ 0xFF, 0xFF, 0xFF };
    }
    else {
        message->color = *text_color;
    }
    message->font = font;
    strcpy(message->text, text);
    message->rect.x = x;
    message->rect.y = y;
    create_texture_for_message(message);
    SDL_QueryTexture(message->texture, NULL, NULL, &message->rect.w, &message->rect.h);
    
    return message;
}

void create_texture_for_message(Message* message)
{
    SDL_Texture* texture;

    SDL_Surface* text_surface = TTF_RenderText_Blended(message->font, message->text, message->color);
    if (!text_surface) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }

    texture = SDL_CreateTextureFromSurface(g_renderer, text_surface);
    if (!texture) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(text_surface);
    message->texture = texture;
}

void init_message()
{
    g_message[M_FPS] = create_message(g_font, (char*)"FPS: ", NULL, 0, 0);
    g_message[M_SCORE] = create_message(g_font, (char*)"Score: ", NULL, SCREEN_WIDTH / 5, 0);
    g_message[M_HEALTH] = create_message(g_font, (char*)"HP: ", NULL, SCREEN_WIDTH * 2 /5, 0);
}


void update_message(Message* message, const char *fmt, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, fmt);
    int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    
    strcpy(message->text, buffer);

    if (message->texture) {
        SDL_DestroyTexture(message->texture);
    }
    create_texture_for_message(message);
    SDL_QueryTexture(message->texture, NULL, NULL, &message->rect.w, &message->rect.h);
}

void update_messages()
{
    //FPS
    static int cooldown = 60;
    if (cooldown-- <= 0) {
        update_message(g_message[M_FPS], "FPS: %.1f", average_fps);
        cooldown = 60;
    }

    //Score
    update_message(g_message[M_SCORE], "Score: %d", score);

    //Health
    if (player) {
        update_message(g_message[M_HEALTH], "HP: %d", player->health);
    }
    else {
        update_message(g_message[M_HEALTH], "HP: 0");
    }
}

void draw_message(Message* message)
{
	SDL_RenderCopy(g_renderer, message->texture, NULL, &message->rect);
}

void draw_messages()
{
    for (int i = 0; i < M_TOTAL; i++) {
        draw_message(g_message[i]);
    }
}




