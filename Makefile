CC = gcc
CFLAGS = -Wall -pedantic -std=c99

INC_DIRS = inc src
SRC_DIRS = src
TEST_DIRS = test
OBJ_DIR_ROOT = obj

SOURCES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJECTS := $(SOURCES:%.c=$(OBJ_DIR_ROOT)/%.o)
INCLUDES := $(foreach dir, $(INC_DIRS), -I$(dir))

TESTS := $(foreach dir, $(TEST_DIRS), $(wildcard $(dir)/*.c))
TEST_OBJECTS := $(TESTS:%.c=$(OBJ_DIR_ROOT)/%.o)

TEST_EXECUTABLE=container_example

TEST_PREFIX=
unit=container_example 	 # This is the file to test. defaults to nstring.c

.PHONY: clean run set-up

set-up:
	$(foreach dir, $(SRC_DIRS), mkdir -p $(OBJ_DIR_ROOT)/$(dir))
	$(foreach dir, $(TEST_DIRS), mkdir -p $(OBJ_DIR_ROOT)/$(dir))

run-valgrind: test
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck ./$(TEST_PREFIX)$(basename $(unit))

$(OBJ_DIR_ROOT)/%.o : %.c set-up
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_EXECUTABLE) : $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

build: $(OBJECTS)

run: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

clean:
	rm -f src/*~ inc/*~ obj/*~ test/*~
	rm -rf obj/*
	rm -f $(TEST_EXECUTABLE)

$(TEST_PREFIX)$(unit): $(TEST_OBJECTS)
	$(foreach dir, $(SRC_DIRS), cp -rf $(OBJ_DIR_ROOT)/$(dir)/* $(OBJ_DIR_ROOT)/$(TEST_DIRS))
	rm $(OBJ_DIR_ROOT)/$(TEST_DIRS)/$(basename $(unit)).o
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(basename $@)

test: build $(TEST_PREFIX)$(unit)
	./$(basename $(TEST_PREFIX)$(unit))
