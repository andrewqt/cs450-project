CC = g++
CFLAGS = -std=c++20

SRC_ALGO_DIR = algos
SRC_TEST_DIR = testing

SRCS_ALGOS = $(wildcard $(SRC_ALGO_DIR)/*.cpp)

EXES_ALGOS = $(patsubst $(SRC_ALGO_DIR)/%.cpp,%,$(SRCS_ALGOS))

SRCS_TESTING = $(wildcard $(SRC_TEST_DIR)/*.cpp)

EXES_TESTING = $(patsubst $(SRC_TEST_DIR)/%.cpp,%,$(SRCS_TESTING))

# Default target
all: $(EXES_ALGOS) $(EXES_TESTING)

# Rule to build each executable
$(EXES_ALGOS): % : algos/%.cpp
	$(CC) $(CFLAGS) $< -o $@

$(EXES_TESTING): % : $(SRC_TEST_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# Clean rule
clean:
	rm -rf $(EXES_ALGOS) $(EXES_TESTING)

# Phony targets
.PHONY: all clean