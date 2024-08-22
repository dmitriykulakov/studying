.PHONY: install uninstall dvi dist tests check valgrind clean git gcov_report
CXX = gcc
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++17
LIBS = -lstdc++ -lpthread -lm 
LTEST = -lgtest
SRC = $(wildcard back/*.cc)
OBJS = $(SRC:.cc=.o)

GCOVFLAGS = --coverage

OS := $(shell uname -s)

ifeq ($(OS),Linux)
	OPEN_CMD := xdg-open
else ifeq ($(OS),Darwin)
	OPEN_CMD := open
endif

all: clean build

build: install

rebuild: clean all

tests: $(OBJS)
	@echo "┏-------------------┓"
	@echo "┃   Testing models  ┃"
	@echo "┗-------------------┛"
	$(CXX) $(CXXFLAGS) tests/maze_test.cc $^ -o maze_test $(LTEST) $(LIBS)
	./maze_test

	
gcov_report: clean
	@echo "┏------------------------------------┓"
	@echo "┃       Generating html report       ┃"
	@echo "┗------------------------------------┛"
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $(SRC) tests/maze_test.cc -o maze_test $(LTEST) $(LIBS)
	./maze_test
	lcov  -t "Report" -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	rm -rf *.gcno *.gcov *.gcda *.info *.a *.dSYM tests/*.o
	@echo "┏-----------------------------┓"
	@echo "┃     HTML report is ready    ┃"
	@echo "┗-----------------------------┛"
	$(OPEN_CMD) ./report/index.html
	
clang:
	@echo "┏------------------------------┓"
	@echo "┃    Clang format correction   ┃"
	@echo "┗------------------------------┛"
	clang-format -style=Google -i **/*.cc **/*.h

clang_check:
	@echo "┏------------------------------┓"
	@echo "┃   Checnking to clang-format  ┃"
	@echo "┗------------------------------┛"
	clang-format -style=Google -n **/*.cc **/*.h

	
install: clean	
	@echo "┏-----------------------------┓"
	@echo "┃     Start installation      ┃"
	@echo "┗-----------------------------┛"
	mkdir -p build
	qmake6 -o build/Makefile front/Maze.pro
	make -C build
	make -C build clean
	rm -rf build/.qmake.stash build/Makefile
	@echo "┏-------------------------------------------------┓"
	@echo "┃        The installation was successful          ┃"
	@echo "┃    The executable file is located in build      ┃"
	@echo "┗-------------------------------------------------┛"


uninstall:
	@echo "┏---------------------------------┓"
	@echo "┃     Uninstalling a program      ┃"
	@echo "┗---------------------------------┛"
	rm -rf build
	@echo "┏---------------------------------┓"
	@echo "┃    The programm is uninstalled  ┃"
	@echo "┗---------------------------------┛"

dist:
	@echo "┏---------------------------------┓"
	@echo "┃     Creating distribution       ┃"
	@echo "┗---------------------------------┛"
	rm -drf ./dist
	mkdir -p ./dist
	cp  build/Maze ./dist
	cp ./README_RUS.md ./dist
	cd ./dist && tar cvzf Maze.tgz *
	rm ./dist/Maze
	rm ./dist/README_RUS.md
	@echo "┏------------------------------------┓"
	@echo "┃    Distribution tgz is ready       ┃"
	@echo "┗------------------------------------┛"

	
dvi:
	open README_RUS.md
	
valgrind: clean tests
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./maze_test 2>>1.txt
	grep ERROR 1.txt

clean:
	@echo "┏-----------------------------┓"	
	@echo "┃   Deleting temporary files  ┃"
	@echo "┗-----------------------------┛"
	rm -rf *.o main maze_test *.gcno *.gcda *.dSYM back/*.o front/*.o report
	rm -rf 1.txt
	rm -drf ./dist
	rm -rf build/generated_maze.txt
