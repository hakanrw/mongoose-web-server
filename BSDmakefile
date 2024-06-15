TARGET_NAME=web

# Compiler and flags
CFLAGS ?= -Wall -Wextra

# Directories
SRC_DIR = src
INCLUDE_DIR = $(SRC_DIR)/include
OBJ_DIR = obj
BIN_DIR = bin

# Files
SRCS = src/mongoose.c src/main.c
DEPS = src/include/mongoose.h src/include/user.h

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
	@RED='\033[31m'; \
	GREEN='\033[32m'; \
	YELLOW='\033[33m'; \
	BLUE='\033[34m'; \
	MAGENTA='\033[35m'; \
	CYAN='\033[36m'; \
	WHITE='\033[37m'; \
	RESET='\033[0m'; \
	fail=0; \
	total=0; \
	for test in test/*; do \
		printf "$${YELLOW}\n+-------------+\nrunning test %s\n+-------------+\n\n$${RESET}" $$test; \
		./$(EXEC) & pid=$$!; \
		sleep 0.5; echo; \
		total=$$((total + 1)); \
		sh "$$test"; \
		ret=$$?; \
		[ $$ret != 0 ] && fail=$$((fail + 1)) && printf "$${RED}\n!-------------!\ntest %s failed\n!-------------!\n\n$${RESET}" $$test; \
		[ $$ret = 0 ] && printf "$${GREEN}\n+-------------+\ntest %s succeeded\n+-------------+\n\n$${RESET}" $$test; \
		kill $$pid; \
		wait $$pid; \
	done; \
	[ $$fail = 0 ] && printf "$${GREEN}\n+-------------+\n%d tests succeeded\n+-------------+\n\n$${RESET}" $$total; \
	[ $$fail != 0 ] && printf "$${RED}\n!-------------!\n%d tests failed\n!-------------!\n\n$${RESET}" $$fail; \
	true

# Phony targets
.PHONY: all clean run test
