#ifndef B_RESHITH_H
#define B_RESHITH_H
#include "cpu.h"
#include "display.h"
#define NS_CYCLE 16666666
int chip8_start(CPU *cpu, display *display, uint8_t *buffer, int size);
void chip8_run (CPU *cpu, display *display);
void chip8_down(CPU *cpu, display *display);
#endif
