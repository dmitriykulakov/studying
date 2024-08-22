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
STATICLIB=s21_math.a
DIROBJ=./obj
DIRFUNCTESTS=./tests
DIRGCOV=./gcov
DIRGENHTML=./genhtml

all: $(STATICLIB) test gcov_report 

rebuild: clean all

$(STATICLIB):
	$(CC) $(CFLAGS) -c ./functions/*.c 
	ar r s21_math.a *.o
	rm -f *.o

test: $(STATICLIB)
	$(CC) $(CFLAGS) -c ./functions/*.c $(GCOVFLAGS) 
	$(CC) $(CFLAGS) -c ./functions_tests/*.c
	mkdir -p $(DIROBJ)  
	mv -f *.o $(DIROBJ)
	
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_abs_test.o $(DIROBJ)/s21_abs.o $(STATICLIB) -o s21_abs_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_acos_test.o $(DIROBJ)/s21_acos.o $(STATICLIB) -o s21_acos_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_asin_test.o $(DIROBJ)/s21_asin.o $(STATICLIB) -o s21_asin_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_atan_test.o $(DIROBJ)/s21_atan.o $(STATICLIB) -o s21_atan_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_ceil_test.o $(DIROBJ)/s21_ceil.o $(STATICLIB) -o s21_ceil_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_cos_test.o $(DIROBJ)/s21_cos.o $(STATICLIB) -o s21_cos_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_exp_test.o $(DIROBJ)/s21_exp.o $(STATICLIB) -o s21_exp_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_fabs_test.o $(DIROBJ)/s21_fabs.o $(STATICLIB) -o s21_fabs_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_floor_test.o $(DIROBJ)/s21_floor.o $(STATICLIB) -o s21_floor_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_fmod_test.o $(DIROBJ)/s21_fmod.o $(STATICLIB) -o s21_fmod_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_log_test.o $(DIROBJ)/s21_log.o $(STATICLIB) -o s21_log_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_pow_test.o $(DIROBJ)/s21_pow.o $(STATICLIB) -o s21_pow_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_sin_test.o $(DIROBJ)/s21_sin.o $(STATICLIB) -o s21_sin_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_sqrt_test.o $(DIROBJ)/s21_sqrt.o $(STATICLIB) -o s21_sqrt_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_tan_test.o $(DIROBJ)/s21_tan.o $(STATICLIB) -o s21_tan_test $(CHECKFLAGS)
	mkdir -p $(DIRFUNCTESTS)  
	mv -f *_test $(DIRFUNCTESTS) 

	make run_test

run_test:	
	$(DIRFUNCTESTS)/s21_abs_test
	$(DIRFUNCTESTS)/s21_acos_test
	$(DIRFUNCTESTS)/s21_asin_test
	$(DIRFUNCTESTS)/s21_atan_test
	$(DIRFUNCTESTS)/s21_ceil_test
	$(DIRFUNCTESTS)/s21_cos_test
	$(DIRFUNCTESTS)/s21_exp_test
	$(DIRFUNCTESTS)/s21_fabs_test
	$(DIRFUNCTESTS)/s21_floor_test
	$(DIRFUNCTESTS)/s21_fmod_test
	$(DIRFUNCTESTS)/s21_log_test
	$(DIRFUNCTESTS)/s21_pow_test
	$(DIRFUNCTESTS)/s21_sin_test
	$(DIRFUNCTESTS)/s21_sqrt_test
	$(DIRFUNCTESTS)/s21_tan_test

gcov_report:
	mkdir -p $(DIRGCOV)
	gcov ./functions/*.c -o ./
	mv -f *.gcov $(DIRGCOV)
	mv -f *.gcda $(DIRGCOV)
	mv -f *.gcno $(DIRGCOV)
	lcov -d $(DIRGCOV) -c -o ./html.info
	genhtml -o $(DIRGENHTML) html.info
	open $(DIRGENHTML)/index.html
	
build: all

check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n *.h
	clang-format -style=Google -i *.h
	clang-format -style=Google -n ./functions/*.c
	clang-format -style=Google -i ./functions/*.c 
	clang-format -style=Google -n ./functions_tests/*.c ./functions_tests/*.h
	clang-format -style=Google -i ./functions_tests/*.c ./functions_tests/*.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions/*.c ./functions/*.h
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions_tests/*.c ./functions_tests/*.h
	rm -f .clang-format
	
clean:
	rm -f *.a
	rm -f *.gc*
	rm -drf $(DIROBJ)
	rm -drf $(DIRFUNCTESTS)
	rm -drf $(DIRGCOV)
	rm -drf $(DIRGENHTML)
	rm -f *.info
	