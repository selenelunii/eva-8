#include "../include/display.h"
#include <stdio.h>
int display_start (display *display)
{
    printf("EVA-8 is starting\n");
    SDL_Init(SDL_INIT_VIDEO);
    display->window = SDL_CreateWindow("EVA-8: A(nother) CHIP-8 emulator",WIDTH * FACTOR_DISPLAY ,HEIGHT * FACTOR_DISPLAY,SDL_WINDOW_RESIZABLE);
    display->render = SDL_CreateRenderer(display->window,NULL);
    display->texture = SDL_CreateTexture(display->render,SDL_PIXELFORMAT_XRGB8888,SDL_TEXTUREACCESS_STREAMING,WIDTH,HEIGHT);
    display->quit = false;
}
void display_draw (display *display)
{

}
void display_close (display *display)
{
    SDL_DestroyTexture(display->texture);
    SDL_DestroyRenderer(display->render);
    SDL_DestroyWindow(display->window);
    SDL_Quit();
}
