CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 

CHECK_FLAGS = -I/usr/local/include -I/opt/homebrew/include
CHECK_LIBS = -L/usr/local/lib -L/opt/homebrew/lib -lcheck -lm -pthread

LIB_NAME = s21_string
LIB_FILE = $(LIB_NAME).a
TEST_SRC = $(LIB_NAME)_test.c
TEST_EXE = test_$(LIB_NAME)
GCOV_REPORT_DIR = coverage_report

SRC_FILES = s21_to_upper.c s21_to_lower.c s21_insert.c s21_trim.c

OBJ_FILES = $(patsubst %.c,%.o,$(SRC_FILES))

GCOV_FLAGS = --coverage

all: $(LIB_FILE) $(TEST_EXE)

$(LIB_FILE): $(OBJ_FILES)
	ar rcs $@ $^

%.o: %.c $(LIB_NAME).h
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_EXE): $(TEST_SRC) $(LIB_FILE)
	$(CC) $(CFLAGS) $(CHECK_FLAGS) $^ -o $@ $(CHECK_LIBS)

test: $(TEST_EXE)
	@echo "--- Running Unit Tests ---"
	./$(TEST_EXE)

gcov_report: clean_gcov
	@echo "--- Generating LCOV Coverage Report ---"
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(SRC_FILES)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS) $(TEST_SRC) $(OBJ_FILES) -o $(TEST_EXE) $(CHECK_LIBS)
	./$(TEST_EXE) > /dev/null 2>&1
	lcov -t "s21_string Coverage" -o lcov.info -c -d .
	@mkdir -p $(GCOV_REPORT_DIR)
	genhtml -o $(GCOV_REPORT_DIR)/html lcov.info
	@echo "\nHTML report is available in: $(GCOV_REPORT_DIR)/html/index.html"
	@OS=$$(uname); \
	if [ "$$OS" = "Darwin" ]; then open $(GCOV_REPORT_DIR)/html/index.html; \
	elif [ "$$OS" = "Linux" ]; then xdg-open $(GCOV_REPORT_DIR)/html/index.html; \
	else echo "Open the report manually: $(GCOV_REPORT_DIR)/html/index.html"; fi


clean_gcov:
	rm -f *.gcda *.gcno *.gcov lcov.info
	rm -rf $(GCOV_REPORT_DIR)


clean: clean_gcov
	rm -f $(OBJ_FILES) $(LIB_FILE) $(TEST_EXE)
	@echo "Cleaned up build files."

cf:
	@echo "---" > .clang-format
	@echo "BasedOnStyle: Google" >> .clang-format
	@clang-format -i *.c *.h
	@rm -f .clang-format

.PHONY: all test clean gcov_report clean_gcov cf