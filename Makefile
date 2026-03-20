CC = clang
TARGET = eva-8
$(TARGET):
	$(CC) src/main.c src/cpu.c src/display.c src/chip8.c -o $(TARGET) -lSDL3
run: $(TARGET)
	./$(TARGET)
clean:
	rm $(TARGET)
