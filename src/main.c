#include "../include/chip8.h"
int main(int argc, char* argv[])
{
    uint8_t buffer;
    CPU cpu_instance;
    display display_instance;
    chip8_start(&cpu_instance,&display_instance,&buffer);
    chip8_run(&cpu_instance, &display_instance);
    chip8_down(&cpu_instance, &display_instance);
    return 0;

}
