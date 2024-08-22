.PHONY: check clean 
CFLAGS= -g -D_POSIX_C_SOURCE=200809L -Wall -Werror -Wextra -std=c11
GCOVFLAGS=-fprofile-arcs -ftest-coverage
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	CHECKFLAGS = -lcheck -lgcov --coverage -lm -lrt -lpthread -lsubunit
	OPEN_CMD = xdg-open
endif

ifeq ($(UNAME_S),Darwin)
	CHECKFLAGS= -lcheck --coverage
	OPEN_CMD = open
endif

all: gcov_report

rebuild: clean all

s21_string.a:
	gcc $(CFLAGS) -c ./functions/*.c
	cp functions/*.h .
	ar rcs s21_string.a *.o
	rm -f *.o

test: clean s21_string.a
	gcc $(CFLAGS) functions_tests/*.c functions/*.c s21_string.a -o s21_test $(CHECKFLAGS)
	mkdir report_files
	mv *.gcno report_files/.
	./s21_test
	mv *.gcda report_files/.
	
gcov_report: test
	lcov --quiet --capture --directory ./report_files --output-file report_files/coverage.info
	lcov --remove report_files/coverage.info '/functions_tests/*' -o report_files/filtered_coverage.info
	lcov --remove report_files/filtered_coverage.info '/usr/local/lib/gcc/10/gcc/x86_64-apple-darwin20/10.3.0/include-fixed' -o report_files/filtered_coverage.info
	genhtml --quiet report_files/filtered_coverage.info --output-directory report
	$(OPEN_CMD) report/index.html



build: all

clang:
	clang-format -style=Google -n ./functions/*.h
	clang-format -style=Google -n ./functions/*.c
	clang-format -style=Google -n ./functions_tests/*.c ./functions_tests/*.h

clean:
	rm -f *.a
	rm -f *.gc*
	rm -drf $(DIROBJ)
	rm -f *.info
	rm -rf report
	rm -rf report_files
	rm -rf s21_test
	rm -rf s21_test.dSYM
	rm -rf *.h

	