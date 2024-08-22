#ifndef PARSING_H_
#define PARSING_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.141592653589793238462643383279502884L

typedef struct data {
  int count_of_vertexes;
  int count_of_facets;
} data_t;

typedef struct Matrix {
  double **matrix;
  int rows;
  int cols;
} matrix_t;

typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

int parsing(
    char *filename, data_t *count, matrix_t *matrix_of_vertexes,
    polygon_t **polygons,
    int *count_edges);  // основная функция в которую надо передавать файл
int create_matrix_t(int rows, matrix_t *result);  // создание матрицы вершин
int file_parsing(char *filename, matrix_t *matrix_of_vertexes,
                 polygon_t *polygons, data_t count,
                 int *count_edges);  // запист координат в матрицу определение
                                     // числа полигонов
void digit_parsing(char *buffer, double *massive, int m);
int polygon_build(char *buffer, polygon_t *polygon, int *count_edges,
                  int vertexes);  //создание полигонов
void center_figure(matrix_t *matrix_of_vertexes);  // центрирование фигуры
void move_figure(matrix_t *matrix_of_vertexes, double x, double y,
                 double z);  // перемещение фигуры
void rotate_figure(matrix_t *matrix_of_vertexes, double x, double y,
                   double z);  // вращение фигуры
void change_figure(matrix_t *matrix_of_vertexes,
                   double n);  // масштабирование фигуры
void free_memory(matrix_t *matrix_of_vertexes, polygon_t **polygons,
                 int n);  //очищение памяти

#endif
