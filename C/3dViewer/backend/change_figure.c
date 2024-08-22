#include "parsing.h"

void move_figure(matrix_t *matrix_of_vertexes, double x, double y, double z) {
  for (int i = 1; i < matrix_of_vertexes->rows; i++) {
    matrix_of_vertexes->matrix[i][0] += x;
    matrix_of_vertexes->matrix[i][1] += y;
    matrix_of_vertexes->matrix[i][2] += z;
  }
}

void rotate_figure(matrix_t *matrix_of_vertexes, double x, double y, double z) {
  x = x / 180 * PI;
  y = y / 180 * PI;
  z = z / 180 * PI;
  for (int i = 1; i < matrix_of_vertexes->rows; i++) {
    if (x != 0) {
      double tmp = matrix_of_vertexes->matrix[i][1];
      matrix_of_vertexes->matrix[i][1] =
          matrix_of_vertexes->matrix[i][1] * cos(x) -
          matrix_of_vertexes->matrix[i][2] * sin(x);
      matrix_of_vertexes->matrix[i][2] =
          tmp * sin(x) + matrix_of_vertexes->matrix[i][2] * cos(x);
    }
    if (y != 0) {
      double tmp = matrix_of_vertexes->matrix[i][0];
      matrix_of_vertexes->matrix[i][0] =
          matrix_of_vertexes->matrix[i][0] * cos(y) +
          matrix_of_vertexes->matrix[i][2] * sin(y);
      matrix_of_vertexes->matrix[i][2] =
          tmp * (-sin(y)) + matrix_of_vertexes->matrix[i][2] * cos(y);
    }
    if (z != 0) {
      double tmp = matrix_of_vertexes->matrix[i][0];
      matrix_of_vertexes->matrix[i][0] =
          matrix_of_vertexes->matrix[i][0] * cos(z) +
          matrix_of_vertexes->matrix[i][1] * (-sin(z));
      matrix_of_vertexes->matrix[i][1] =
          tmp * sin(z) + matrix_of_vertexes->matrix[i][1] * cos(z);
    }
  }
}

void change_figure(matrix_t *matrix_of_vertexes, double n) {
  for (int i = 1; i < matrix_of_vertexes->rows; i++) {
    matrix_of_vertexes->matrix[i][0] *= n;
    matrix_of_vertexes->matrix[i][1] *= n;
    matrix_of_vertexes->matrix[i][2] *= n;
  }
}
