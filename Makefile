TARGET_NAME=web

ifndef TARGET_NAME
$(error TARGET_NAME is not set)
endif

# Compiler and flags
CFLAGS ?= -Wall -Wextra

# Directories
SRC_DIR = src
INCLUDE_DIR = $(SRC_DIR)/include
OBJ_DIR = obj
BIN_DIR = bin

# Files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(wildcard $(INCLUDE_DIR)/*.h)

# Executable name
EXEC = $(BIN_DIR)/$(TARGET_NAME)

# Default target
all: $(EXEC)

# Rule for creating object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Rule for creating the executable
$(EXEC): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(EXEC)
	./$(EXEC)

test: $(EXEC)
	@printf "\n+-------------+\nrunning tests...\n+-------------+\n\n"; \
	./$(EXEC) & pid=$$!; \
	sleep 1; \
	fail=0; \
	for test in test/*; do \
		printf "\n+-------------+\nrunning test %s\n+-------------+\n\n" $$test; \
		sh "$$test"; \
		ret=$$?; \
		[ $$ret != 0 ] && fail=$$((fail + 1)) && printf "\n!-------------!\ntest %s failed\n!-------------!\n" $$test; \
		[ $$ret = 0 ] && printf "\n+-------------+\ntest %s succeeded\n+-------------+\n" $$test; \
	done; \
	kill $$pid; \
	wait $$pid; \
	[ $$fail = 0 ] && printf "\n+-------------+\nall tests succeeded\n+-------------+\n\n"; \
	[ $$fail != 0 ] && printf "\n!-------------!\n%d tests failed\n!-------------!\n\n" $$fail; \
	true

# Phony targets
.PHONY: all clean run test
