CC := clang

BUILD := release


TARGET := eva-8

OBJDIR := build/
SRCDIR := src/

CFILES := $(SRCDIR)main.c $(SRCDIR)cpu.c $(SRCDIR)display.c $(SRCDIR)chip8.c
OBJS := $(OBJDIR)main.o $(OBJDIR)cpu.o $(OBJDIR)display.o $(OBJDIR)chip8.o
LIBS := -lSDL3

DFLAGS := -g -fsanitize=address,undefined,leak -fno-omit-frame-pointer
CFLAGS := -std=c23 -Wall -Werror -Iinclude

.PHONY: all clean

all : $(TARGET)

$(TARGET) : $(OBJS)
ifeq ($(BUILD),debug)
	$(CC) $(DFLAGS) $(OBJS) -o $(TARGET) $(LIBS)
else
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)
endif

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
ifeq ($(BUILD),debug)
	$(CC) -MD $(DFLAGS) $(CFLAGS) -c $< -o $@
else
	$(CC) -MD $(CFLAGS) -c $< -o $@
endif
-include $(OBJDIR)*.d

clean:
	rm -rf $(TARGET) $(OBJDIR)*.o $(OBJDIR)*.d
