TARGET_NAME = web

# Compiler and flags
CFLAGS ?= -Wall -Wextra -pedantic

# Directories
SRC_DIR = src
INCLUDE_DIR = $(SRC_DIR)/include
OBJ_DIR = obj
BIN_DIR = bin

# Files
SRCS = src/mongoose.c src/main.c src/arch.c
DEPS = src/include/mongoose.h src/include/user.h src/include/arch.h

OBJS = ${SRCS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

# Executable name
EXEC = $(BIN_DIR)/$(TARGET_NAME)

# Default target
all: $(EXEC)

.OBJDIR: ./ # stop BSD insanity

# Rule for creating the executable
$(EXEC): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) ${OBJS} -o ${.TARGET}

$(OBJS): $(@:${OBJ_DIR}/%.o=${SRC_DIR}/%.c)	
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o ${.TARGET} -c $(@:${OBJ_DIR}/%.o=${SRC_DIR}/%.c)

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(EXEC)
	./$(EXEC)

test: $(EXEC)
	./test.sh

# Phony targets
.PHONY: all clean run test
