.PHONY: check clean
FLAGS=gcc -D_POSIX_C_SOURCE=200809L -Wall -Werror -Wextra -ggdb -std=c11
GCOVFLAGS=-fprofile-arcs -ftest-coverage 
OS=$(shell uname -s)
ifeq ($(OS),Linux)
CHECKFLAGS=-lcheck -lsubunit -lrt -lpthread -lm -lgcov --coverage
endif
ifeq ($(OS),Darwin)   
CHECKFLAGS=-lcheck -lgcov --coverage
endif

all: install

build: all

rebuild: clean all

test:
	$(FLAGS) -c backend/s21_smart_calculator.c $(GCOVFLAGS) 
	$(FLAGS) -c backend/s21_smart_calculator_test.c
	
	$(FLAGS)  s21_smart_calculator_test.o ./s21_smart_calculator.o -o s21_smart_calculator_test $(CHECKFLAGS)
	
	./s21_smart_calculator_test
	
gcov_report:
	mkdir -p ./gcov
	gcov s21_smart_calculator.c -o ./
	mv -f *.gcov ./gcov
	mv -f *.gcda ./gcov
	mv -f *.gcno ./gcov
	lcov -d ./gcov -c -o ./html.info
	genhtml -o ./genhtml html.info
	open ./genhtml/index.html
	
check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n ./front/*.h
	clang-format -style=Google -i ./front/*.h
	clang-format -style=Google -n ./front/*.cpp
	clang-format -style=Google -i ./front/*.cpp  
	clang-format -style=Google -n ./backend/*.h
	clang-format -style=Google -i ./backend/*.h
	clang-format -style=Google -n ./backend/*.c
	clang-format -style=Google -i ./backend/*.c 
#	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions/*.c 
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions_tests/*.c ./functions_tests/*.h
	rm -f .clang-format
	
	
install:
	make clean
	cd front && qmake6 && make && make clean
	rm -f ./front/Makefile
	mv ./front/s21_smart_calculator ./
	
uninstall:
	rm -rf s21_smart_calculator

dist:
	make clean
	tar cvzf ../s21_smart_calculator_archive.tgz front backend Makefile
	mv ../s21_smart_calculator_archive.tgz ./
	
dvi:
	open README_RUS.md
	
valgrind: clean test
	
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./s21_smart_calculator_test 2>>1.txt
	
	grep ERROR 1.txt

clean:
	rm -f *.txt
	rm -drf ./gcov
	rm -f *.gc*
	rm -drf ./genhtml
	rm -f *.info
	rm -f *.o
	rm -f s21_smart_calculator_test
	rm -f *.tgz
	rm -rf s21_smart_calculator
