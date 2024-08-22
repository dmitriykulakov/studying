.PHONY: check clean
CC=gcc -D_POSIX_C_SOURCE=200809L
CFLAGS=-Wall -Werror -Wextra -ggdb -std=c11
GCOVFLAGS=-fprofile-arcs -ftest-coverage 
OS=$(shell uname -s)
ifeq ($(OS),Linux)
CHECKFLAGS=-lcheck -lsubunit -lrt -lpthread -lm -lgcov --coverage
endif
ifeq ($(OS),Darwin)   
CHECKFLAGS=-lcheck -lgcov --coverage
endif
STATICLIB=s21_decimal.a
DIROBJ=./obj
DIRFUNCTESTS=./tests
DIRGCOV=./gcov
DIRGENHTML=./genhtml

all: $(STATICLIB) test gcov_report 

build: all

rebuild: clean all

$(STATICLIB):
	$(CC) $(CFLAGS) -c ./functions/*.c 
	ar r $(STATICLIB) *.o
	rm -f *.o

test: $(STATICLIB)
	$(CC) $(CFLAGS) -c ./functions/*.c $(GCOVFLAGS) 
	$(CC) $(CFLAGS) -c ./functions_tests/*.c
	mkdir -p $(DIROBJ)  
	mv -f *.o $(DIROBJ)
	
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_add_test.o $(DIROBJ)/s21_add.o $(STATICLIB) -o s21_add_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_sub_test.o $(DIROBJ)/s21_sub.o $(STATICLIB) -o s21_sub_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_mul_test.o $(DIROBJ)/s21_mul.o $(STATICLIB) -o s21_mul_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_div_test.o $(DIROBJ)/s21_div.o $(STATICLIB) -o s21_div_test $(CHECKFLAGS)

	$(CC) $(CFLAGS)  $(DIROBJ)/s21_is_less_test.o $(DIROBJ)/s21_is_less.o $(STATICLIB) -o s21_is_less_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_is_less_or_equal_test.o $(DIROBJ)/s21_is_less_or_equal.o $(STATICLIB) -o s21_is_less_or_equal_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_is_greater_test.o $(DIROBJ)/s21_is_greater.o $(STATICLIB) -o s21_is_greater_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_is_greater_or_equal_test.o $(DIROBJ)/s21_is_greater_or_equal.o $(STATICLIB) -o s21_is_greater_or_equal_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_is_equal_test.o $(DIROBJ)/s21_is_equal.o $(STATICLIB) -o s21_is_equal_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_is_not_equal_test.o $(DIROBJ)/s21_is_not_equal.o $(STATICLIB) -o s21_is_not_equal_test $(CHECKFLAGS)
	
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_from_int_to_decimal_test.o $(DIROBJ)/s21_from_int_to_decimal.o $(STATICLIB) -o s21_from_int_to_decimal_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_from_float_to_decimal_test.o $(DIROBJ)/s21_from_float_to_decimal.o $(STATICLIB) -o s21_from_float_to_decimal_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_from_decimal_to_int_test.o $(DIROBJ)/s21_from_decimal_to_int.o $(STATICLIB) -o s21_from_decimal_to_int_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_from_decimal_to_float_test.o $(DIROBJ)/s21_from_decimal_to_float.o $(STATICLIB) -o s21_from_decimal_to_float_test $(CHECKFLAGS)
	
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_floor_test.o $(DIROBJ)/s21_floor.o $(STATICLIB) -o s21_floor_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_round_test.o $(DIROBJ)/s21_round.o $(STATICLIB) -o s21_round_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_truncate_test.o $(DIROBJ)/s21_truncate.o $(STATICLIB) -o s21_truncate_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_negate_test.o $(DIROBJ)/s21_negate.o $(STATICLIB) -o s21_negate_test $(CHECKFLAGS)

	mkdir -p $(DIRFUNCTESTS) 
	mv -f *_test $(DIRFUNCTESTS) 
	make run_test

run_test:	
	$(DIRFUNCTESTS)/s21_add_test
	$(DIRFUNCTESTS)/s21_sub_test
	$(DIRFUNCTESTS)/s21_mul_test
	$(DIRFUNCTESTS)/s21_div_test
	
	$(DIRFUNCTESTS)/s21_is_less_test
	$(DIRFUNCTESTS)/s21_is_less_or_equal_test
	$(DIRFUNCTESTS)/s21_is_greater_test
	$(DIRFUNCTESTS)/s21_is_greater_or_equal_test
	$(DIRFUNCTESTS)/s21_is_equal_test
	$(DIRFUNCTESTS)/s21_is_not_equal_test
	
	$(DIRFUNCTESTS)/s21_from_int_to_decimal_test
	$(DIRFUNCTESTS)/s21_from_float_to_decimal_test
	$(DIRFUNCTESTS)/s21_from_decimal_to_int_test
	$(DIRFUNCTESTS)/s21_from_decimal_to_float_test
	
	$(DIRFUNCTESTS)/s21_floor_test
	$(DIRFUNCTESTS)/s21_round_test
	$(DIRFUNCTESTS)/s21_truncate_test
	$(DIRFUNCTESTS)/s21_negate_test

gcov_report:
	mkdir -p $(DIRGCOV)
	gcov ./functions/*.c -o ./
	mv -f *.gcov $(DIRGCOV)
	mv -f *.gcda $(DIRGCOV)
	mv -f *.gcno $(DIRGCOV)
	lcov -d $(DIRGCOV) -c -o ./html.info
	genhtml -o $(DIRGENHTML) html.info
	open $(DIRGENHTML)/index.html
	
check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n *.h
	clang-format -style=Google -i *.h
	clang-format -style=Google -n ./functions/*.c
	clang-format -style=Google -i ./functions/*.c 
	clang-format -style=Google -n ./functions_tests/*.c ./functions_tests/*.h
	clang-format -style=Google -i ./functions_tests/*.c ./functions_tests/*.h
#	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions/*.c 
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions_tests/*.c ./functions_tests/*.h
	rm -f .clang-format
	
valgrind: clean test
	
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_add_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_sub_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_mul_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_div_test

	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_is_less_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_is_less_or_equal_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_is_greater_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_is_greater_or_equal_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_is_equal_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_is_not_equal_test
	
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_from_int_to_decimal_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_from_float_to_decimal_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_from_decimal_to_int_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_from_decimal_to_float_test
	
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_floor_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_round_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_truncate_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_negate_test

clean:
	rm -f *.a
	rm -f *.gc*
	rm -drf $(DIROBJ)
	rm -drf $(DIRFUNCTESTS)
	rm -drf $(DIRGCOV)
	rm -drf $(DIRGENHTML)
	rm -f *.info