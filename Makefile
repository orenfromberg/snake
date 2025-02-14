# Define the compiler
CC = gcc

# Define compiler flags
CFLAGS = -Wall -Wextra -g -I/usr/incude/SDL2
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf -lm

# Define the target executable name
TARGET = snake

# Define the source files
SOURCES = main.c snake.c snake_math.c

# Define the object files (automatically generated)
OBJECTS = $(SOURCES:.c=.o)

# Default rule (what happens when you just type "make")
$(TARGET): $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Rule to compile .c files to .o files
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

test: test.o snake.o snake_math.o
		$(CC) $(CFLAGS) test.o snake.o snake_math.o $(LDFLAGS) -o test 

# Clean rule (removes the compiled files)
clean:
		rm -f $(TARGET) $(OBJECTS)

# Phony target (not a real file, just a label for a command)
.PHONY: clean