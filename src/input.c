#include "input.h"
#include <SDL3/SDL_main.h>
void event(CPU *cpu, display *display)
{
    SDL_Event event; // temporal, i going to create an event.h later or something like that
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_EVENT_QUIT)
        {
            display->quit = true;
        }
    }
}
