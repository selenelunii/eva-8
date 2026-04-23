#include "chip8.h"
#include <stdio.h>
#include "input.h"
int chip8_start(CPU *cpu, display *display, uint8_t *buffer, int size)
{
    printf("EVA-8 STARTING \n");
    cpu_start(cpu);
    memcpy((cpu->ram)+0x200,buffer,size);
    display_start(display);
    return 0;
}
void chip8_run (CPU *cpu, display *display)
{
    while(!(display->quit))
    {
        uint64_t start_time = SDL_GetTicksNS();
        event(cpu, display);
        for(int i = 0; i < 12; i++)
        {
            cpu_step(cpu);
        }
        update_timers(cpu);
        display_draw(display, cpu->display);
        uint64_t end_time = SDL_GetTicksNS();
        uint64_t work_time = end_time - start_time;
        if (work_time < NS_CYCLE)
        {
            SDL_DelayPrecise(NS_CYCLE - work_time);
        }
    }
}
void chip8_down(CPU *cpu, display *display)
{
    printf("GOODBYE WORLD!\n");
    display_close(display);
}
