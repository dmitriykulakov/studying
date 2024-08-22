#include "parsing.h"

int parsing(char *filename, data_t *count, matrix_t *matrix_of_vertexes,
            polygon_t **polygons, int *count_edges) {
  int function_result = 0;
  matrix_of_vertexes->rows = 0;
  count->count_of_facets = 0;
  count->count_of_vertexes = 0;
  if (strstr(filename, ".obj") == NULL) return 4;
  FILE *obj;
  obj = fopen(filename, "r");
  if (obj != NULL) {
    char buffer[4096];
    while (fgets(buffer, 4096, obj) != NULL) {
      int buffer_size = strlen(buffer);
      if (buffer_size > 2) {
        if (buffer[0] == 'v' && buffer[1] == ' ') count->count_of_vertexes++;
        if (buffer[0] == 'f' && buffer[1] == ' ') count->count_of_facets++;
      }
    }
    count->count_of_vertexes++;
    count->count_of_facets++;
    if (count->count_of_vertexes < 5 || count->count_of_facets < 5)
      function_result = 2;
    else if ((create_matrix_t(count->count_of_vertexes, matrix_of_vertexes) &&
              function_result) == 0) {
      *polygons =
          (polygon_t *)malloc((count->count_of_facets) * sizeof(polygon_t));
      if (*polygons == NULL)
        function_result = 1;
      else {
        for (int i = 1; i < count->count_of_facets; i++) {
          (*polygons)[i].vertexes = NULL;
          (*polygons)[i].numbers_of_vertexes_in_facets = 0;
        }
      }
    } else
      function_result = 1;
    fclose(obj);
    if (function_result == 0)
      function_result = file_parsing(filename, matrix_of_vertexes, *polygons,
                                     *count, count_edges);
    if (function_result == 0) center_figure(matrix_of_vertexes);
  } else
    function_result = 3;
  return function_result;
}

int create_matrix_t(int rows, matrix_t *result) {
  int function_result = 0;
  if (rows < 2)
    function_result = 1;
  else {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix == NULL) function_result = 1;
  }
  for (int i = 0; i < rows && function_result == 0; i++) {
    result->matrix[i] = (double *)malloc(3 * sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      function_result = 1;
    }
  }
  result->rows = rows;
  result->cols = 3;
  return function_result;
}

int file_parsing(char *filename, matrix_t *matrix_of_vertexes,
                 polygon_t *polygons, data_t count, int *count_edges) {
  int function_result = 0, vertex = 1, polygon = 1;
  FILE *obj;
  obj = fopen(filename, "r");
  char buffer[4096];
  while (fgets(buffer, 4096, obj) != NULL && function_result == 0) {
    if (buffer[0] == 'v' && buffer[1] == ' ') {
      digit_parsing(buffer, matrix_of_vertexes->matrix[vertex], 3);
      vertex++;
    }
    if (buffer[0] == 'f' && buffer[1] == ' ') {
      function_result = polygon_build(buffer, &polygons[polygon], count_edges,
                                      count.count_of_vertexes);
      polygon++;
    }
  }
  fclose(obj);
  *count_edges = *count_edges / 2;
  return function_result;
}

void digit_parsing(char *buffer, double *massive, int m) {
  int buffer_size = strlen(buffer);
  for (int j = 2, n = 0; n < m && j < buffer_size; j++) {
    int minus_flag = 0, vertex_flag = 0;
    if (buffer[j] == '-') {
      minus_flag = 1;
      j++;
    }
    massive[n] = 0;
    for (; buffer[j] >= '0' && buffer[j] <= '9'; j++) {
      massive[n] = massive[n] * 10 + (buffer[j] - 48);
      vertex_flag = 1;
    }
    if (buffer[j] == '.' && vertex_flag == 1) {
      j++;
      int k = 0;
      double tmp = 0;
      for (; buffer[j] >= '0' && buffer[j] <= '9'; j++, k++) {
        tmp = tmp * 10 + (buffer[j] - 48);
      }
      for (int m = 0; m < k; m++) {
        tmp = tmp / 10;
      }
      massive[n] += tmp;
    }
    if (minus_flag == 1 && vertex_flag == 1) massive[n] *= (-1);
    if (vertex_flag == 1) {
      n++;
    }
    for (; buffer[j] != ' ' && j < buffer_size; j++)
      ;
    if (n == 3) j--;
  }
}

int polygon_build(char *buffer, polygon_t *polygon, int *count_edges,
                  int vertexes_) {
  int function_result = 0;
  int buffer_size = strlen(buffer);
  polygon->numbers_of_vertexes_in_facets = 0;
  for (int j = 1; j < buffer_size; j++) {
    for (; buffer[j] != ' ' && j < buffer_size - 1; j++)
      ;
    if (j < buffer_size) {
      if (buffer[j + 1] == '-' ||
          (buffer[j + 1] >= '0' && buffer[j + 1] <= '9'))
        (polygon->numbers_of_vertexes_in_facets)++;
    }
  }
  *count_edges += polygon->numbers_of_vertexes_in_facets;
  if (polygon->numbers_of_vertexes_in_facets < 3)
    function_result = 2;
  else {
    polygon->vertexes =
        (int *)malloc((polygon->numbers_of_vertexes_in_facets) * sizeof(int));
    for (int k = 0; k < polygon->numbers_of_vertexes_in_facets; k++) {
      polygon->vertexes[k] = 0;
    }
    if (polygon->vertexes != NULL) {
      for (int j = 2, n = 0; j < buffer_size; j++) {
        int minus_flag = 0, vertex_flag = 0;
        if (buffer[j] == '-') {
          minus_flag = 1;
          j++;
        }
        for (; buffer[j] >= '0' && buffer[j] <= '9'; j++) {
          polygon->vertexes[n] = (polygon->vertexes[n] * 10) + (buffer[j] - 48);
          vertex_flag = 1;
        }
        if (minus_flag == 1 && vertex_flag == 1)
          polygon->vertexes[n] = vertexes_ - polygon->vertexes[n];
        if (vertex_flag == 1) {
          n++;
        }
        for (; buffer[j] != ' ' && j < buffer_size; j++)
          ;
      }
    } else
      function_result = 1;
  }
  return function_result;
}

void center_figure(matrix_t *matrix_of_vertexes) {
  double x_max = matrix_of_vertexes->matrix[1][0];
  double x_min = matrix_of_vertexes->matrix[1][0];
  double y_max = matrix_of_vertexes->matrix[1][1];
  double y_min = matrix_of_vertexes->matrix[1][1];
  double z_max = matrix_of_vertexes->matrix[1][2];
  double z_min = matrix_of_vertexes->matrix[1][2];
  for (int i = 1; i < matrix_of_vertexes->rows; i++) {
    if (matrix_of_vertexes->matrix[i][0] > x_max)
      x_max = matrix_of_vertexes->matrix[i][0];
    if (matrix_of_vertexes->matrix[i][0] < x_min)
      x_min = matrix_of_vertexes->matrix[i][0];
    if (matrix_of_vertexes->matrix[i][1] > y_max)
      y_max = matrix_of_vertexes->matrix[i][1];
    if (matrix_of_vertexes->matrix[i][1] < y_min)
      y_min = matrix_of_vertexes->matrix[i][1];
    if (matrix_of_vertexes->matrix[i][2] > z_max)
      z_max = matrix_of_vertexes->matrix[i][2];
    if (matrix_of_vertexes->matrix[i][2] < z_min)
      z_min = matrix_of_vertexes->matrix[i][2];
  }
  double center_x = (x_max + x_min) / 2;
  double center_y = (y_max + y_min) / 2;
  double center_z = (z_max + z_min) / 2;
  for (int i = 1; i < matrix_of_vertexes->rows; i++) {
    matrix_of_vertexes->matrix[i][0] -= center_x;
    matrix_of_vertexes->matrix[i][1] -= center_y;
    matrix_of_vertexes->matrix[i][2] -= center_z;
  }
}
