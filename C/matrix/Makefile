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

all: s21_matrix.a test gcov_report 

build: all

rebuild: clean all

s21_matrix.a:
	$(FLAGS) -c ./functions/*.c 
	ar r s21_matrix.a *.o
	rm -f *.o

test: s21_matrix.a
	$(FLAGS) -c ./functions/*.c $(GCOVFLAGS) 
	$(FLAGS) -c ./functions_tests/*.c
	mkdir -p ./obj  
	mv -f *.o ./obj
	
	$(FLAGS)  ./obj/s21_create_matrix_test.o ./obj/s21_create_matrix.o ./obj/s21_remove_matrix.o s21_matrix.a -o s21_create_matrix_test $(CHECKFLAGS)
	$(FLAGS)  ./obj/s21_sum_matrix_test.o ./obj/s21_sum_matrix.o s21_matrix.a -o s21_sum_matrix_test $(CHECKFLAGS)
	$(FLAGS)  ./obj/s21_sub_matrix_test.o ./obj/s21_sub_matrix.o s21_matrix.a -o s21_sub_matrix_test $(CHECKFLAGS)
	$(FLAGS)  ./obj/s21_mult_number_test.o ./obj/s21_mult_number.o s21_matrix.a -o s21_mult_number_test $(CHECKFLAGS)
	$(FLAGS)  ./obj/s21_mult_matrix_test.o ./obj/s21_mult_matrix.o s21_matrix.a -o s21_mult_matrix_test $(CHECKFLAGS)
	$(FLAGS)  ./obj/s21_transpose_test.o ./obj/s21_transpose.o s21_matrix.a -o s21_transpose_test $(CHECKFLAGS)
	$(FLAGS)  ./obj/s21_calc_complements_test.o ./obj/s21_calc_complements.o s21_matrix.a -o s21_calc_complements_test $(CHECKFLAGS)
	$(FLAGS)  ./obj/s21_determinant_test.o ./obj/s21_determinant.o s21_matrix.a -o s21_determinant_test $(CHECKFLAGS)
	$(FLAGS)  ./obj/s21_inverse_matrix_test.o ./obj/s21_inverse_matrix.o s21_matrix.a -o s21_inverse_matrix_test $(CHECKFLAGS)
	$(FLAGS)  ./obj/s21_eq_matrix_test.o ./obj/s21_eq_matrix.o s21_matrix.a -o s21_eq_matrix_test $(CHECKFLAGS)

	mkdir -p ./tests 
	mv -f *_test ./tests 
	make run_test

run_test:	
	./tests/s21_create_matrix_test
	./tests/s21_sum_matrix_test
	./tests/s21_sub_matrix_test
	./tests/s21_mult_number_test
	./tests/s21_mult_matrix_test
	./tests/s21_transpose_test
	./tests/s21_calc_complements_test
	./tests/s21_determinant_test
	./tests/s21_inverse_matrix_test
	./tests/s21_eq_matrix_test

gcov_report:
	mkdir -p ./gcov
	gcov ./functions/*.c -o ./
	mv -f *.gcov ./gcov
	mv -f *.gcda ./gcov
	mv -f *.gcno ./gcov
	lcov -d ./gcov -c -o ./html.info
	genhtml -o ./genhtml html.info
	open ./genhtml/index.html
	
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
	
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_create_matrix_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_sum_matrix_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_sub_matrix_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_mult_number_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_mult_matrix_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_transpose_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_calc_complements_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_determinant_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_inverse_matrix_test 2>>1.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/s21_eq_matrix_test 2>>1.txt

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
