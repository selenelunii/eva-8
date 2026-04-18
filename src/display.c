#include "display.h"
#include <stdio.h>
int display_start (display *display)
{
    display->quit = true;
    printf("EVA-8 is starting\n");
    SDL_Init(SDL_INIT_VIDEO);
    display->window = SDL_CreateWindow("EVA-8: A(nother) CHIP-8 emulator",WIDTH * FACTOR_DISPLAY ,HEIGHT * FACTOR_DISPLAY,SDL_WINDOW_RESIZABLE);
    if (display->window == NULL)
    {
        fprintf(stderr,"ERROR creating window: %s", SDL_GetError());
        return 1;
    }
    display->render = SDL_CreateRenderer(display->window,NULL);
    if (display->render == NULL)
    {
        fprintf(stderr,"ERROR creating render: %s", SDL_GetError());
        return 1;
    }
    display->texture = SDL_CreateTexture(display->render,SDL_PIXELFORMAT_XRGB8888,SDL_TEXTUREACCESS_STREAMING,WIDTH,HEIGHT);
    if (display->texture == NULL)
    {
        fprintf(stderr,"ERROR creating texture: %s", SDL_GetError());
        return 1;
    }
    SDL_SetTextureScaleMode(display->texture, SDL_SCALEMODE_PIXELART);
    display->quit = false;
    return 0;
}
void display_draw (display *display, uint8_t *buffer)
{
    for(int i = 0; i < (WIDTH *  HEIGHT); i++)
    {
        display->real_display[i] = buffer[i] ? 0x00FFFFFF : 0x00000000;
    }
    SDL_UpdateTexture(display->texture,NULL,display->real_display, 64 * sizeof(uint32_t));
    SDL_RenderTexture(display->render,display->texture,NULL,NULL);
    SDL_RenderPresent(display->render);
}
void display_close (display *display)
{
    SDL_DestroyTexture(display->texture);
    SDL_DestroyRenderer(display->render);
    SDL_DestroyWindow(display->window);
    SDL_Quit();
}
