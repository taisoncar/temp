#include "setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "entity.h"
#include "message.h"
#include "enemy.h"
#include "projectile.h"
#include "player.h"

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
TTF_Font* g_font = NULL;
SDL_Texture* g_texture[T_TOTAL] = {};

void init_SDL(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    g_window = SDL_CreateWindow( "Pong", 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_WIDTH, SCREEN_HEIGHT, 
                                SDL_WINDOW_SHOWN);
    if (!g_window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetVSync(g_renderer, 1);
    if (!g_renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    printf("SDL initialized successfully\n");
}

void close_SDL()
{
    //Messages
    destroy_messages();

    //Entities
    destroy_enemy_list();
    destroy_bullet_list();
    kill_player();

    //Font
    TTF_CloseFont(g_font);

    //Textures
    for (int i = 0; i < T_TOTAL; i++) {
        SDL_DestroyTexture(g_texture[i]);
        //TODO: error catchhing
    }
    
    //System
    SDL_DestroyRenderer(g_renderer);
    g_renderer = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    printf("SDL closed successfully\n");
}

SDL_Texture* load_texture(char* path)
{
    SDL_Texture* texture;

    printf("Loading texture: %s\n", path);

    texture = IMG_LoadTexture(g_renderer, path);
    if (texture == NULL) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, IMG_GetError());
    }

    return texture;
}

void init_texture()
{
    g_texture[T_PLAYER] = load_texture("../res/img/ship.png");
    g_texture[T_BULLET] = load_texture("../res/img/bullet.png");
    g_texture[T_ENEMY] = load_texture("../res/img/enemy.png");
}

void load_font()
{
    g_font = TTF_OpenFont("../res/font/mfont.ttf", 40);
    if (!g_font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
}
