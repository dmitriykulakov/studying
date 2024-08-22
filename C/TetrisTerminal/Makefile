.PHONY: install uninstall dvi dist test check valgrind clean git
FLAGS=gcc -D_POSIX_C_SOURCE=200809L -Wall -Werror -Wextra -ggdb -std=c11
GCOVFLAGS=-fprofile-arcs -ftest-coverage 
OS=$(shell uname -s)
ifeq ($(OS),Linux)
CHECKFLAGS=-lcheck -lsubunit -lrt -lpthread -lm -lgcov --coverage
endif
ifeq ($(OS),Darwin)   
CHECKFLAGS=-lcheck -lgcov --coverage
endif

all: clean install

build: all

rebuild: clean uninstall all

test: clean
	$(FLAGS) -c ./brick_game/tetris/model.c $(GCOVFLAGS)
	$(FLAGS) -c ./tests/tetris_test.c
	$(FLAGS)  ./tetris_test.o ./model.o -o s21_tetris_test $(CHECKFLAGS)
	./s21_tetris_test

gcov_report:
	mkdir -p ./gcov
	gcov ./brick_game/tetris/model.c -o ./
	mv -f *.gcda ./gcov
	mv -f *.gcno ./gcov
	lcov -d ./gcov -c -o ./html.info
	genhtml -o ./genhtml html.info
	open ./genhtml/index.html
	
check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n ./brick_game/tetris/*.h
	clang-format -style=Google -i ./brick_game/tetris/*.h
	clang-format -style=Google -n ./brick_game/tetris/*.c
	clang-format -style=Google -i ./brick_game/tetris/*.c  
	clang-format -style=Google -n ./gui/cli/*.h
	clang-format -style=Google -i ./gui/cli/*.h
	clang-format -style=Google -n ./gui/cli/*.c
	clang-format -style=Google -i ./gui/cli/*.c 
#	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions/*.c 
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions_tests/*.c ./functions_tests/*.h
	rm -f .clang-format
	
install: clean
	$(FLAGS) -c ./gui/cli/front.c ./brick_game/tetris/model.c -lncurses
	$(FLAGS) ./*o -lncurses -o s21_tetris
	mv -f s21_tetris ./Out

uninstall:
	rm -rf ./Out/s21_tetris

dist:
	rm -drf ./dist
	mkdir -p ./dist
	cp  ./Out/s21_tetris ./dist
	cp ./README_RUS.md ./dist
	cd ./dist && tar cvzf s21_tetris.tgz *
	rm ./dist/s21_tetris
	rm ./dist/README_RUS.md
	
dvi:
	open README_RUS.md
	
valgrind: test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./s21_tetris_test 2>>1.txt
	grep ERROR 1.txt
	
clean:
	rm -f 1.txt
	rm -drf ./gcov
	rm -f *.gc*
	rm -drf ./genhtml
	rm -f *.info
	rm -f *.o
	rm -f ./s21_tetris_test
	rm -drf ./dist
