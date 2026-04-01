#include "../include/chip8.h"
#include <stdio.h>
int chip8_start(CPU *cpu, display *display, uint8_t *buffer, int size)
{
    cpu_start(cpu);
    memcpy((cpu->ram)+0x200,buffer,size);
    printf("ROM - START\n");
    for(int i = 0; i < size; i++)
    {
        printf("ram[0x%x] : 0x%x\n",0x200+i,cpu->ram[0x200 + i]);
    }
    printf("ROM - END\n");
    display_start(display);
    return 0;
}
void chip8_run (CPU *cpu, display *display)
{
    printf("WIP\n");
    while(!(display->quit))
    {
        uint64_t start_time = SDL_GetTicksNS();
        for(int i = 0; i < 12; i++)
        {
            cpu_step(cpu);SDL_DelayPrecise(NS_CYCLE);
        }
        uint64_t end_time = SDL_GetTicksNS();
        uint64_t work_time = start_time - end_time;
        if (work_time < NS_CYCLE)
        {
            SDL_DelayPrecise(NS_CYCLE - work_time);
        }
    }
}
void chip8_down(CPU *cpu, display *display)
{
    display_close(display);
}
