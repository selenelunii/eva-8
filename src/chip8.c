#include "../include/chip8.h"
#include <stdio.h>
int chip8_start(CPU *cpu, display *display, uint8_t *buffer)
{
    cpu_start(cpu);
    display_draw(display);
    return 0;
}
void chip8_run (CPU *cpu, display *display)
{
    printf("WIP\n");
    while(!(display->quit))
    {

    }
}
void chip8_down(CPU *cpu, display *display)
{
    display_close(display);
}
