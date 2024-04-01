CC = g++
CFLAGS = -std=c++20
SRC_DIR = algos

# List all source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Generate corresponding executable names
EXES = $(patsubst $(SRC_DIR)/%.cpp,%,$(SRCS))

# Default target
all: $(EXES)

# Rule to build each executable
$(EXES): % : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# Clean rule
clean:
	rm -rf $(EXES)

# Phony targets
.PHONY: all clean