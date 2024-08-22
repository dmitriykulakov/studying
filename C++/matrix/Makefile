.PHONY: check clean
CC=gcc
FLAGS= -ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++
GCOVFLAGS= --coverage -fno-elide-constructors
OS=$(shell uname -s)
ifeq ($(OS),Linux)
CHECKFLAGS= -lgtest -lsubunit -lm -lpthread --coverage 
endif
ifeq ($(OS),Darwin)   
CHECKFLAGS=-lgtest -lgtest_main -lm -lpthread -fprofile-arcs -ftest-coverage 
endif

all: s21_matrix_oop.a test gcov_report 

build: all

rebuild: clean all

s21_matrix_oop.a:
	$(CC) $(FLAGS) -c ./functions/*.cpp 
	ar r s21_matrix_oop.a *.o
	rm -f *.o

test: s21_matrix_oop.a
	$(CC) $(FLAGS) -c ./functions/*.cpp $(GCOVFLAGS) 
	$(CC) $(FLAGS) -c ./function_tests/*.cpp
	mkdir -p ./obj  
	mv -f *.o ./obj
	
	
	$(CC) ./obj/s21_matrix_Sum_test.o ./obj/s21_matrix_Sum.o s21_matrix_oop.a -o s21_matrix_Sum_test $(CHECKFLAGS) $(FLAGS)
	$(CC) ./obj/s21_matrix_Sub_test.o ./obj/s21_matrix_Sub.o s21_matrix_oop.a -o s21_matrix_Sub_test $(CHECKFLAGS) $(FLAGS)
	$(CC) ./obj/s21_matrix_Mul_test.o ./obj/s21_matrix_Mul.o s21_matrix_oop.a -o s21_matrix_Mul_test $(CHECKFLAGS) $(FLAGS)
	$(CC)  ./obj/s21_matrix_transpose_test.o ./obj/s21_matrix_transpose.o s21_matrix_oop.a -o s21_matrix_transpose_test $(CHECKFLAGS) $(FLAGS)
	$(CC)  ./obj/s21_matrix_calc_test.o ./obj/s21_matrix_calc.o s21_matrix_oop.a -o s21_matrix_calc_test $(CHECKFLAGS) $(FLAGS)
	$(CC)  ./obj/s21_matrix_determinant_test.o ./obj/s21_matrix_determinant.o s21_matrix_oop.a -o s21_matrix_determinant_test $(CHECKFLAGS) $(FLAGS)
	$(CC)  ./obj/s21_matrix_inverse_test.o ./obj/s21_matrix_inverse.o s21_matrix_oop.a -o s21_matrix_inverse_test $(CHECKFLAGS) $(FLAGS)
	$(CC)  ./obj/s21_matrix_equal_test.o ./obj/s21_matrix_equal.o s21_matrix_oop.a -o s21_matrix_equal_test $(CHECKFLAGS) $(FLAGS)
	$(CC)  ./obj/s21_matrix_test.o ./obj/s21_matrix.o s21_matrix_oop.a -o s21_matrix_test $(CHECKFLAGS) $(FLAGS)
	
	mkdir -p ./tests 
	mv -f *_test ./tests 
	make run_test

run_test:	
	./tests/s21_matrix_Sum_test
	./tests/s21_matrix_Sub_test
	./tests/s21_matrix_Mul_test
	./tests/s21_matrix_transpose_test
	./tests/s21_matrix_calc_test
	./tests/s21_matrix_determinant_test
	./tests/s21_matrix_inverse_test
	./tests/s21_matrix_equal_test
	./tests/s21_matrix_test

gcov_report:
	mkdir -p ./gcov
	gcov ./functions/*.cpp -o ./
	mv -f *.gcov ./gcov
	mv -f *.gcda ./gcov
	mv -f *.gcno ./gcov
	lcov -d ./gcov -c -o ./html.info
	genhtml -o ./genhtml html.info
	open ./genhtml/index.html
	
check:
#	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n *.h
	clang-format -style=Google -i *.h
	clang-format -style=Google -n ./functions/*.cpp
	clang-format -style=Google -i ./functions/*.cpp 
	clang-format -style=Google -n ./function_tests/*.cpp ./function_tests/*.h
	clang-format -style=Google -i ./function_tests/*.cpp ./function_tests/*.h
#	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
#	cppcheck --enable=all --suppress=missingIncludeSystem ./functions/*.c 
#	cppcheck --enable=all --suppress=missingIncludeSystem ./function_tests/*.c ./function_tests/*.h
	rm -f .clang-format
	
valgrind: clean test
	
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_matrix_Sum_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_matrix_Sub_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_matrix_Mul_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_matrix_transpose_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_matrix_calc_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_matrix_determinant_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_matrix_inverse_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_matrix_equal_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_matrix_test 2>>1.txt
	grep ERROR 1.txt

clean:
	rm -f *.txt
	rm -f *.a
	rm -f *.gc*
	rm -drf ./obj
	rm -drf ./tests
	rm -drf ./gcov
	rm -drf ./genhtml
	rm -f *.info
