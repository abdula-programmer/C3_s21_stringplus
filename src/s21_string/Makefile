CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
AR = ar rcs

OBJ_DIR = obj
LIB = s21_string.a

SRCS = $(filter-out tests.c, $(wildcard *.c))
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(LIB) $(OBJS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB)
	$(CC) $(CFLAGS) tests.c $(LIB) -o test_program -lcheck
	./test_program

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(LIB) test_program quick_test

rebuild: clean all

format:
	clang-format -n $(SRCS) tests.c

.PHONY: all test clean rebuild format