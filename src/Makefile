CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
AR = ar rcs

OBJ_DIR = obj
LIB = s21_string.a

SRCS := $(shell find . -name "*.c")
OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(LIB) $(OBJS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: s21_string.a
	$(CC) $(CFLAGS) main.c s21_string.a -o test_s21_string
	./test_s21_string


clean:
	rm -rf $(OBJ_DIR)
	rm -f $(LIB)

rebuild: clean all

format:
	clang-format -i $(SRCS)

.PHONY: all clean rebuild format