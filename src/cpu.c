#include "cpu.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static const uint8_t font[] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
void cpu_start(CPU *cpu)
{
    memset(cpu->ram, 0x00, sizeof(cpu->ram));
    memset(cpu->display, 0x00, sizeof(cpu->display));
    memset(cpu->stack, 0x00, sizeof(cpu->stack));
    memset(cpu->v, 0x00, sizeof(cpu->v));
    cpu->pc = 0x200;
    cpu->i = 0x0;
    cpu->sound = 0x0;
    cpu->delay = 0x0;
    cpu->sp = 0x0;
    memcpy(cpu->ram,font,sizeof(font));
}
void cpu_step(CPU *cpu)
{
    uint16_t opcode = (cpu->ram[cpu->pc] << 0x8) | (cpu->ram[cpu->pc+1]);
    uint16_t NNN = opcode & 0x0FFF;
    uint8_t NN = opcode & 0x00FF;
    uint8_t N = opcode & 0x000F;
    uint8_t X = (opcode & 0x0F00)>> 0x08;
    uint8_t Y = (opcode & 0x00F0)>> 0x04;
    uint8_t pixel_x;
    uint8_t pixel_y;
    uint8_t pixel;
    cpu->pc += 2;
    switch(opcode >> 0xC)
    {
        case 0x0:
            switch(NN)
            {
                case 0xE0:
                    memset(cpu->display, 0x00, sizeof(cpu->display));
                    break;
                case 0xEE:
                    cpu->sp--;
                    cpu->pc = cpu->stack[cpu->sp];
                    break;
            }
            break;
        case 0x1:
            cpu->pc = NNN;
            break;
        case 0x2:
            cpu->stack[cpu->sp] = cpu->pc;
            cpu->sp++;
            cpu->pc = NNN;
            break;
        case 0x3:
            if(cpu->v[X] == NN)
            {
                cpu->pc += 2;
            }
            break;
        case 0x4:
            if(cpu->v[X] != NN)
            {
                cpu->pc += 2;
            }
            break;
        case 0x5:
            if(cpu->v[X] == cpu->v[Y])
            {
                cpu->pc += 2;
            }
            break;
        case 0x6:
            cpu->v[X] = NN;
            break;
        case 0x7:
            cpu->v[X] += NN;
            break;
        case 0x8:
            switch(N)
            {
                case 0x0:
                    cpu->v[X] = cpu->v[Y];
                    break;
                case 0x1:
                    cpu->v[X] |= cpu->v[Y];
                    break;
                case 0x2:
                    cpu->v[X] &= cpu->v[Y];
                    break;
                case 0x3:
                    cpu->v[X] ^= cpu->v[Y];
                    break;
                case 0x4:
                    if((uint16_t) cpu->v[X] + (uint16_t) cpu->v[Y] > 255 )
                    {
                        cpu->v[0xF] = 1;
                    }
                    else
                    {
                        cpu->v[0xF] = 0;
                    }
                    cpu->v[X] += cpu->v[Y];
                    break;
                case 0x5:
                    if(cpu->v[X] >= cpu->v[Y])
                    {
                        cpu->v[0xF] = 1;
                    }
                    else
                    {
                        cpu->v[0xF] = 0;
                    }
                    cpu->v[X] = cpu->v[X] - cpu->v[Y];
                    break;
                case 0x6:
                    cpu->v[X] = cpu->v[Y] >> 1;
                    cpu->v[0xF] = cpu->v[Y] & 0x1;
                    break;
                case 0x7:
                    if(cpu->v[Y] >= cpu->v[X])
                    {
                        cpu->v[0xF] = 1;
                    }
                    else
                    {
                        cpu->v[0xF] = 0;
                    }
                    cpu->v[X] = cpu->v[Y] - cpu->v[X];
                    break;
                case 0xE:
                    cpu->v[X] = cpu->v[Y] << 1;
                    cpu->v[0xF] = (cpu->v[Y] & 0x80) >> 7;
                    break;
            }
            break;
        case 0x9:
            if(cpu->v[X] != cpu->v[Y])
            {
                cpu->pc += 2;
            }
            break;
        case 0xA:
            cpu->i = NNN;
            break;
        case 0xB:
            cpu->pc = NNN + cpu->v[0x0];
            break;
        case 0xC:
            cpu->v[X] = (rand() % 256) & NN;
            break;
        case 0xD:
            pixel_x = cpu->v[X] % 64;
            pixel_y = cpu->v[Y] % 32;
            cpu->v[0x0F] = 0;
            for (int col = 0; col < N; col++)
            {
                for(int row = 0; row < 8; row++)
                {
                    if ((pixel_x + row < 64) && (pixel_y + col < 32))
                    {
                        pixel = (cpu->ram[cpu->i + col] >> (7 - row)) &  0x01;
                        if ((cpu->display[(pixel_x + row) + ((pixel_y + col) * 64)] == 1) && (pixel) == 1)
                        {
                            cpu->v[0x0F] = 1;
                        }
                        cpu->display [(pixel_x + row) + ((pixel_y + col ) * 64 )] ^= pixel;
                    }
                }
            }
            break;
        case 0xF:
            switch(NN)
            {
                case 0x07:
                    cpu->v[X] = cpu->delay;
                    break;
                case 0x15:
                    cpu->delay = cpu->v[X];
                    break;
            }
            break;
        default :
            printf("INSTRUCTION NOT IMPLEMENTED: 0x%x in Memory address [0x%x] \n", opcode >> 0xC, (cpu->pc) - 2 );
    }
}

void update_timers(CPU *cpu)
{
    if (cpu->delay > 0)
    {
        cpu->delay--;
    }
    if (cpu->sound > 0)
    {
        cpu->sound--;
    }
}
