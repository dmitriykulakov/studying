.PHONY: check clean
CC=g++
CFLAGS= -ggdb -Wall -Werror -Wextra
GCOVFLAGS=--coverage -fno-elide-constructors
OS=$(shell uname -s)

ifeq ($(OS),Linux)
LDFLAGS=-lgtest  -lm -lpthread --coverage 
endif
ifeq ($(OS),Darwin)   
LDFLAGS=-lgtest -lgtest_main -lm -lpthread -fprofile-arcs -ftest-coverage 
endif

DIROBJ=./obj
DIRGTEST=./gtest
DIRGCOV=./gcov
DIRGENHTML=./genhtml

all: install

build: all

rebuild: clean all

test:	clean
	$(CC) $(CFLAGS) -c ./tests/s21_brick_game_test.cpp
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c ./brick_game/snake/model_s.cpp
	mkdir -p $(DIROBJ)  
	mv -f *.o $(DIROBJ)
	
	$(CC) $(DIROBJ)/*.o -o ./s21_brick_game_test $(LDFLAGS) $(CFLAGS)
	./s21_brick_game_test
	
gcov_report: test
	mkdir -p $(DIRGCOV)
	gcov ./brick_game/snake/front_s.cpp -o ./ 
	mv -f *.gcda $(DIRGCOV)
	mv -f *.gcno $(DIRGCOV)
	lcov  -d $(DIRGCOV) -c -o ./html.info
	lcov --remove html.info '/usr/include/*' -o filtered_html.info
	genhtml -o $(DIRGENHTML) filtered_html.info
	open $(DIRGENHTML)/index.html
	
check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n ./brick_game/snake/*.h
	clang-format -style=Google -i ./brick_game/snake/*.h
	clang-format -style=Google -n ./brick_game/snake/*.cpp
	clang-format -style=Google -i ./brick_game/snake/*.cpp
	clang-format -style=Google -n ./brick_game/tetris/*.h
	clang-format -style=Google -i ./brick_game/tetris/*.h
	clang-format -style=Google -n ./brick_game/tetris/*.c
	clang-format -style=Google -i ./brick_game/tetris/*.c
	clang-format -style=Google -n ./gui/cli/*.h
	clang-format -style=Google -i ./gui/cli/*.h
	clang-format -style=Google -n ./gui/cli/*.cc
	clang-format -style=Google -i ./gui/cli/*.cc
	clang-format -style=Google -n ./gui/desktop/*.h
	clang-format -style=Google -i ./gui/desktop/*.h
	clang-format -style=Google -n ./gui/desktop/*.cpp
	clang-format -style=Google -i ./gui/desktop/*.cpp
#	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions/*.c 
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions_tests/*.c ./functions_tests/*.h
	rm -f .clang-format
	
	
install:
	make clean

	$(CC) $(CFLAGS) ./gui/cli/front.cc ./brick_game/tetris/model.c ./brick_game/snake/model_s.cpp -lstdc++ -lncurses -o BrickGame_terminal
#	$(CC) $(CFLAGS) ./*o -lstdc++ -lncurses -o BrickGame_terminal

	cd gui/desktop && /usr/bin/qmake6 && make && make clean
	rm -f ./gui/desktop/Makefile
	mv ./gui/desktop/BrickGame ./

	

uninstall:
	rm -rf BrickGame
	rm -rf BrickGame_terminal

dist:
	rm -drf ./dist
	mkdir -p ./dist
	cp  ./BrickGame ./dist
	cp ./high_score_snake.txt ./dist
	cp ./high_score_tetris.txt ./dist
	cp ./README_RUS.md ./dist
	cd ./dist && tar cvzf BrickGame.tgz *
	rm ./dist/BrickGame
	rm ./dist/high_score_tetris.txt
	rm ./dist/high_score_snake.txt
	rm ./dist/README_RUS.md
	
dvi:
	open README_RUS.md
	
valgrind: clean test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./s21_brick_game_test

clean:
	rm -drf ./gcov
	rm -drf ./obj
	rm -f *.gc*
	rm -drf ./genhtml
	rm -f *.info
	rm -f *.o
	rm -f s21_brick_game_test
	rm -drf ./dist
