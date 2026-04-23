#include "input.h"
#include <SDL3/SDL_main.h>
void event(CPU *cpu, display *display)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_EVENT_QUIT)
        {
            display->quit = true;
        }
        if(event.type == SDL_EVENT_KEY_DOWN)
        {
            switch (event.key.scancode)
            {
                case SDL_SCANCODE_1:
                    cpu->keyboard[0x1] = true;
                    break;
                case SDL_SCANCODE_2:
                    cpu->keyboard[0x2] = true;
                    break;
                case SDL_SCANCODE_3:
                    cpu->keyboard[0x3] = true;
                    break;
                case SDL_SCANCODE_4:
                    cpu->keyboard[0xC] = true;
                    break;
                case SDL_SCANCODE_Q:
                    cpu->keyboard[0x4] = true;
                    break;
                case SDL_SCANCODE_W:
                    cpu->keyboard[0x5] = true;
                    break;
                case SDL_SCANCODE_E:
                    cpu->keyboard[0x6] = true;
                    break;
                case SDL_SCANCODE_R:
                    cpu->keyboard[0xD] = true;
                    break;
                case SDL_SCANCODE_A:
                    cpu->keyboard[0x7] = true;
                    break;
                case SDL_SCANCODE_S:
                    cpu->keyboard[0x8] = true;
                    break;
                case SDL_SCANCODE_D:
                    cpu->keyboard[0x9] = true;
                    break;
                case SDL_SCANCODE_F:
                    cpu->keyboard[0xE] = true;
                    break;
                case SDL_SCANCODE_Z:
                    cpu->keyboard[0xA] = true;
                    break;
                case SDL_SCANCODE_X:
                    cpu->keyboard[0x0] = true;
                    break;
                case SDL_SCANCODE_C:
                    cpu->keyboard[0xB] = true;
                    break;
                case SDL_SCANCODE_V:
                    cpu->keyboard[0xF] = true;
                    break;
                default:
                    break;
            }
        }
        if(event.type == SDL_EVENT_KEY_UP)
        {
            switch (event.key.scancode)
            {
                case SDL_SCANCODE_1:
                    cpu->keyboard[0x1] = false;
                    break;
                case SDL_SCANCODE_2:
                    cpu->keyboard[0x2] = false;
                    break;
                case SDL_SCANCODE_3:
                    cpu->keyboard[0x3] = false;
                    break;
                case SDL_SCANCODE_4:
                    cpu->keyboard[0xC] = false;
                    break;
                case SDL_SCANCODE_Q:
                    cpu->keyboard[0x4] = false;
                    break;
                case SDL_SCANCODE_W:
                    cpu->keyboard[0x5] = false;
                    break;
                case SDL_SCANCODE_E:
                    cpu->keyboard[0x6] = false;
                    break;
                case SDL_SCANCODE_R:
                    cpu->keyboard[0xD] = false;
                    break;
                case SDL_SCANCODE_A:
                    cpu->keyboard[0x7] = false;
                    break;
                case SDL_SCANCODE_S:
                    cpu->keyboard[0x8] = false;
                    break;
                case SDL_SCANCODE_D:
                    cpu->keyboard[0x9] = false;
                    break;
                case SDL_SCANCODE_F:
                    cpu->keyboard[0xE] = false;
                    break;
                case SDL_SCANCODE_Z:
                    cpu->keyboard[0xA] = false;
                    break;
                case SDL_SCANCODE_X:
                    cpu->keyboard[0x0] = false;
                    break;
                case SDL_SCANCODE_C:
                    cpu->keyboard[0xB] = false;
                    break;
                case SDL_SCANCODE_V:
                    cpu->keyboard[0xF] = false;
                    break;
                default:
                    break;
            }
        }
    }
}
