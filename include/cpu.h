#ifndef CPU_H
#define CPU_H
#include <stdint.h>
typedef struct
{
    uint8_t ram[0x1000];
    uint8_t display[64 * 32];
    uint16_t pc;
    uint16_t i;
    uint8_t sp;
    uint16_t stack[0x10];
    uint8_t v[0x10];
    uint8_t delay;
    uint8_t sound;
}CPU;
void cpu_start(CPU *cpu);
void cpu_step(CPU *cpu);
#endif 
