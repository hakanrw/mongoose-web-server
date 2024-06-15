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


RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
MAGENTA=\033[35m
CYAN=\033[36m
WHITE=\033[37m
RESET=\033[0m

test: $(EXEC)
	@fail=0; \
	total=0; \
	for test in test/*; do \
		printf "${YELLOW}\n+-------------+\nrunning test %s\n+-------------+\n\n${RESET}" $$test; \
		./$(EXEC) & pid=$$!; \
		sleep 0.5; echo; \
		total=$$((total + 1)); \
		sh "$$test"; \
		ret=$$?; \
		[ $$ret != 0 ] && fail=$$((fail + 1)) && printf "${RED}\n!-------------!\ntest %s failed\n!-------------!\n\n${RESET}" $$test; \
		[ $$ret = 0 ] && printf "${GREEN}\n+-------------+\ntest %s succeeded\n+-------------+\n\n${RESET}" $$test; \
		kill $$pid; \
		wait $$pid; \
	done; \
	[ $$fail = 0 ] && printf "${GREEN}\n+-------------+\n%d tests succeeded\n+-------------+\n\n${RESET}" $$total; \
	[ $$fail != 0 ] && printf "${RED}\n!-------------!\n%d tests failed\n!-------------!\n\n${RESET}" $$fail; \
	true

# Phony targets
.PHONY: all clean run test
