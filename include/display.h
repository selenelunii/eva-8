#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL3/SDL.h>
#include <stdbool.h>
#define WIDTH 64
#define HEIGHT 32
#define FACTOR_DISPLAY 10
typedef struct
{
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Texture  *texture;
    uint32_t real_display[WIDTH * HEIGHT];
    bool quit;
}display;
int display_start (display *display);
void display_draw (display *display, uint8_t *buffer);
void display_close (display *display);
#endif
