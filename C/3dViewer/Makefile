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

all: install

build: all

rebuild: clean all

test:
	$(FLAGS) backend/*.c $(GCOVFLAGS) $(CHECKFLAGS) -o s21_viever_test
	
	./s21_viever_test
	
gcov_report:
	mkdir -p ./gcov
	gcov backend/change_figure.c backend/free_memory.c backend/parsing.c -o ./
#	mv -f *.gcov ./gcov
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
	cd front && /usr/bin/qmake6 && make && make clean
	rm -f ./front/Makefile
	mv ./front/3D_VIEVER_V0_1 ./

#	make clean
#	cd front && qmake && make && make clean
#	rm -f ./front/Makefile
#	mv ./front/3D_VIEVER_V0_1 ./

uninstall:
	rm -rf 3D_VIEVER_V0_1

dist:

	rm -drf ./dist
	mkdir -p ./dist
	cp  ./3D_VIEVER_V0_1 ./dist
	cp ./settings.ini ./dist
	cp ./README_RUS.md ./dist
	cd ./dist && tar cvzf 3D_VIEVER_V0_1.tgz *
	rm ./dist/3D_VIEVER_V0_1
	rm ./dist/settings.ini
	rm ./dist/README_RUS.md
	
dvi:
	open README_RUS.md
	
valgrind: clean test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./s21_viever_test 2>>1.txt
	grep ERROR 1.txt

clean:
	rm -f *.txt
	rm -drf ./gcov
	rm -f *.gc*
	rm -drf ./genhtml
	rm -f *.info
	rm -f *.o
	rm -f s21_viever_test
	rm -drf ./dist
	rm -rf 3D_VIEVER_V0_1
