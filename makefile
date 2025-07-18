# Compiler and flags
#mingw32-make on windows
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source files (ADD NEW FILES HERE)
SRC = muc.c linked_list.c token.c token_types.c ast_node.c tokenizer.c ast.c arena.c code_generation.c hashtable.c
# Object files (derived from source files)
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = muc

# Default rule
all: $(TARGET)

# Linking step
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Compilation step for each .c file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Debug rule for valgrind
debug: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET) test.mu

# Clean rule to remove generated files
clean:
ifeq ($(OS),Windows_NT)
	del /f /q $(OBJ) $(TARGET) 2>nul || true
else
	rm -f $(OBJ) $(TARGET)
endif

# Phony targets
.PHONY: all clean debug
