.PHONY: check clean
CC=g++
CFLAGS=-Wall -Werror -Wextra -ggdb -std=c++17
GCOVFLAGS=-fprofile-arcs -ftest-coverage -fno-elide-constructors

OS=$(shell uname -s)
ifeq ($(OS),Linux)
LDFLAGS=-lgtest -pthread -lgcov --coverage
endif
ifeq ($(OS),Darwin)   
LDFLAGS=-lgtest -pthread -lgcov --coverage
endif

STATICLIB=s21_containers_oop.a
DIROBJ=./obj
DIRGTEST=./gtest
DIRGCOV=./gcov
DIRGENHTML=./genhtml

all: check test valgrind gcov_report

build: all

rebuild: clean all

test:
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c ./tests/*.cpp 
	mkdir -p $(DIROBJ)  
	mv -f *.o $(DIROBJ)
	
	$(CC) $(DIROBJ)/*.o $(LDFLAGS) -o ./s21_container_tests.out
	mkdir -p $(DIRGTEST)  
	mv -f *.out $(DIRGTEST)
	
	make run_test

run_test:
	$(DIRGTEST)/s21_container_tests.out

gcov_report:
	mkdir -p $(DIRGCOV)
	gcov ./tests/*.cpp -o ./ 
	mv -f *.gcov $(DIRGCOV)
	mv -f *.gcda $(DIRGCOV)
	mv -f *.gcno $(DIRGCOV)
	lcov  -d $(DIRGCOV) -c -o ./html.info
	lcov --remove html.info '/usr/include/*' -o filtered_html.info
	genhtml -o $(DIRGENHTML) filtered_html.info
	open $(DIRGENHTML)/index.html

check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n ./*.h
	clang-format -style=Google -i ./*.h
	clang-format -style=Google -n ./tests/*.cpp ./tests/*.h
	clang-format -style=Google -i ./tests/*.cpp ./tests/*.h
#	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ --std=c++17 ./*.h ./tests/*.cpp ./tests/*.h
	rm -f .clang-format
	
valgrind: 
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRGTEST)/s21_container_tests.out

clean:
	rm -f *.a
	rm -f *.o
	rm -f *.out
	rm -f *.txt
	rm -f *.info
	rm -f *.gc*
	rm -drf $(DIROBJ)
	rm -drf $(DIRGTEST)   
	rm -drf $(DIRGCOV)
	rm -drf $(DIRGENHTML)
	

	
	