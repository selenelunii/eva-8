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

    }
}
void chip8_down(CPU *cpu, display *display)
{
    display_close(display);
}
