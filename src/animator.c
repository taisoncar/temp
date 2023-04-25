#include "animator.h"
#include <SDL.h>
#include <stdio.h>
#include "setup.h"

Animation create_animation(char *path, float frame_interval)
{
    Animation animation;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    animation.texture = load_texture(path);

    int total_length;
    SDL_QueryTexture(animation.texture, NULL, NULL, &total_length, &animation.wh);

    animation.frame_count = total_length / animation.wh;
    animation.frame_interval = frame_interval;

    return animation;
}

void start_animation(Animator *animator, Animation animation)
{
    if (animator->animation.texture != animation.texture) {
        animator->animation = animation;
        animator->frame_index = 0;
        animator->timer = animation.frame_interval;
    }
}

void update_animator(Animator *animator, float delta_time)
{
    if (animator->timer <= 0) {
        animator->frame_index = (animator->frame_index + 1) % animator->animation.frame_count;
        animator->timer = animator->animation.frame_interval;
    }
    animator->timer -= delta_time;
}

SDL_Rect get_animation_rect(Animator animator)
{
    SDL_Rect src;
    src.x = animator.animation.wh * animator.frame_index;
    src.y = 0;
    src.w = src.h = animator.animation.wh;

    return src;
}