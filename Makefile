# Makefile

# Compiler and flags
CC = gcc
CFLAGS = `pkg-config --cflags glfw3`
LDFLAGS = `pkg-config --libs glfw3`

# Source files and target
SRC = src/main.c src/window.c src/util.c
OBJ = $(SRC:.c=.o)
TARGET = program

# Default target
all: $(TARGET)

# Linking the program
$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) -lGL

# Compiling source files
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -lGL

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)