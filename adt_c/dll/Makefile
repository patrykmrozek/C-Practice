# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -std=c99

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source and Object Files
SRC_FILES = $(SRC_DIR)/main.c \
            $(SRC_DIR)/dll.c 

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
OUTPUT = dll

# Rule to create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Rule to link object files and create the executable
$(OUTPUT): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(OUTPUT) 

# Clean up object files and executable
clean:
	rm -f $(OBJ_DIR)/*.o $(OUTPUT)

# Rebuild the project (clean and then build)
rebuild: clean $(OUTPUT)

# Run the program
run: $(OUTPUT)
	./$(OUTPUT)

# Declare non-file targets
.PHONY: clean rebuild run
