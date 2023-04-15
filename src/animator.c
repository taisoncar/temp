#include "animator.h"
#include <SDL.h>
#include <stdio.h>
#include "setup.h"

Animation create_animation(char* path, float frame_interval)
{
    Animation animation;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    animation.texture = load_texture(path);
    int animation_length;
    SDL_QueryTexture(animation.texture, NULL, NULL, &animation_length, &animation.wh);
    animation.frame_count = animation_length / animation.wh;
    animation.frame_index = 0;
    animation.frame_interval = frame_interval;
    animation.frame_timer = frame_interval;

    return animation;
}

void play_animation(Animation* animation, SDL_Rect dest)
{
    SDL_Rect src;
    src.x = animation->wh * animation->frame_index;
    src.y = 0;
    src.w = animation->wh;
    src.h = animation->wh;

    SDL_RenderCopy(g_renderer, animation->texture, &src, &dest);

    if (animation->frame_timer-- <= 0) {
        animation->frame_index = (animation->frame_index + 1) % animation->frame_count;
        animation->frame_timer = animation->frame_interval;
    }
}