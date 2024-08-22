FLAGS = -Wall -Werror -Wextra
CC = gcc

all: s21_grep

s21_grep: s21_grep.c grep.c
	$(CC) $(FLAGS) s21_grep.c grep.c -o ./s21_grep

rebuild: 
	make clean
	make all

clean:
	rm -rf *.o
	rm -rf ./s21_grep
