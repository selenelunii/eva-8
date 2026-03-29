#include "../include/chip8.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int size_rom(FILE *file);
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr,"Usage: ./eva-8 rom_name\n");
        return 1;
    }
    CPU cpu_instance;
    display display_instance;
    FILE *file = fopen(argv[1],"rb");
    if  (file == NULL)
    {
        fprintf(stderr,"ERROR READING ROM\n");
        return -1;
    }
    int file_size = size_rom(file);
    uint8_t *buffer = malloc(sizeof(uint8_t) * file_size);
    if (buffer == NULL)
    {
        fprintf(stderr,"ERROR ALLOCATING MEMORY\n");
        return 1;
    }
    fread(buffer,sizeof(uint8_t), file_size, file);
    fclose(file);
    chip8_start(&cpu_instance,&display_instance,buffer, file_size);
    chip8_run(&cpu_instance, &display_instance);
    chip8_down(&cpu_instance, &display_instance);
    return 0;
}
int size_rom(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    int file_size = ftell(file);
    rewind(file);
    return file_size;
}
