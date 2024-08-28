# Compiler
CC = gcc
ASM = nasm -f win64   # use 'elf64' for linux

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Include directories
INCLUDE_DIRS = -Iinclude/common -Iinclude/platform/arm64 -Iinclude/platform/x86_64

# Source files
COMMON_SRC = $(SRC_DIR)/common/_cpu_interface.c 
PLATFORM_SRC_X86_64 = $(SRC_DIR)/platform/x86_64/_cpu_preprocess.c 

# Object files
COMMON_OBJ = $(OBJ_DIR)/common/_cpu_interface.o 
PLATFORM_OBJ_X86_64 = $(OBJ_DIR)/platform/x86_64/_cpu_preprocess.o 

# Targets
TARGET = cpu_analyzer.exe

# File paths and names might differ; adjust accordingly.
ASM_SRC = ./src/platform/x86_64/utils/cpuidIsSupported.asm  
ASM_OBJ = build/obj/cpuidIsSupported.o  
C_SRCS = main.c ./src/common/_cpu_interface.c ./src/platform/x86_64/_cpu_preprocess.c  
OBJS = $(C_SRCS:.c=.o) $(ASM_OBJ)


all: directories $(BIN_DIR)/$(TARGET)

directories:
	mkdir -p $(OBJ_DIR)/common 
	mkdir -p $(OBJ_DIR)/platform/x86_64 
	mkdir -p $(BIN_DIR)

check-paths:
	@echo "Checking if required files exist..."
	@test -e "$(ASM_SRC)" || (echo "$(ASM_SRC) not found" && exit 1)
	@echo "All required source files are present."

$(ASM_OBJ): $(ASM_SRC) 
	$(ASM) $< -o $@

$(OBJ_DIR)/common/%.o: $(SRC_DIR)/common/%.c
	$(CC) -c $< -o $@ $(INCLUDE_DIRS)

$(OBJ_DIR)/platform/x86_64/%.o: $(SRC_DIR)/platform/x86_64/%.c
	$(CC) -c $< -o $@ $(INCLUDE_DIRS)

$(BIN_DIR)/$(TARGET): $(COMMON_OBJ) $(PLATFORM_OBJ_X86_64) $(ASM_OBJ)
	$(CC) main.c  $^  -o $@  # Link object files, not source files directly

clean:
	rm -rf build/*

.PHONY: all clean directories