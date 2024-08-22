FLAGS = -Wall -Werror -Wextra
CC = gcc

all: s21_cat

s21_cat: s21_cat.c cat.c
	$(CC) $(FLAGS) s21_cat.c cat.c -o ./s21_cat

rebuild: 
	make clean
	make all

clean:
	rm -rf *.o
	rm -rf ./s21_cat
