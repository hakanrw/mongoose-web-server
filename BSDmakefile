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
	@RED='\033[0;31m'; \
	GREEN='\033[0;32m'; \
	YELLOW='\033[0;33m'; \
	BLUE='\033[0;34m'; \
	MAGENTA='\033[0;35m'; \
	CYAN='\033[0;36m'; \
	WHITE='\033[0;37m'; \
	RESET='\033[0m'; \
	fail=0; \
	total=0; \
	for test in test/*; do \
		printf "\n$${YELLOW}+-------------+\n$${YELLOW}running test %s\n$${YELLOW}+-------------+\n\n$${RESET}" $$test; \
		./$(EXEC) & pid=$$!; \
		sleep 0.5; echo; \
		total=$$((total + 1)); \
		sh "$$test"; \
		ret=$$?; \
		[ $$ret != 0 ] && fail=$$((fail + 1)) && printf "\n$${RED}!-------------!\n$${RED}test %s failed\n!$${RED}-------------!\n\n$${RESET}" $$test; \
		[ $$ret = 0 ] && printf "\n$${GREEN}+-------------+\n$${GREEN}test %s succeeded\n$${GREEN}+-------------+\n\n$${RESET}" $$test; \
		kill $$pid; \
		wait $$pid; \
	done; \
	[ $$fail = 0 ] && printf "\n$${GREEN}+-------------+\n$${GREEN}%d tests succeeded\n$${GREEN}+-------------+\n\n$${RESET}" $$total; \
	[ $$fail != 0 ] && printf "\n$${RED}!-------------!\n$${RED}%d tests failed\n$${RED}!-------------!\n\n$${RESET}" $$fail; \
	true

# Phony targets
.PHONY: all clean run test
