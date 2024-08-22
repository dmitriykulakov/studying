#include "parsing.h"

void free_memory(matrix_t *matrix_of_vertexes, polygon_t **polygons, int n) {
  if (matrix_of_vertexes->matrix != NULL) {
    for (int i = 0; i < matrix_of_vertexes->rows; i++) {
      if (matrix_of_vertexes->matrix[i] != NULL) {
        free(matrix_of_vertexes->matrix[i]);
        matrix_of_vertexes->matrix[i] = NULL;
      }
    }
    free(matrix_of_vertexes->matrix);
    matrix_of_vertexes->matrix = NULL;
  }
  if (*polygons != NULL) {
    for (int i = 1; i < n; i++) {
      if ((*polygons)[i].vertexes != NULL) {
        free((*polygons)[i].vertexes);
        (*polygons)[i].vertexes = NULL;
      }
    }
    free(*polygons);
    *polygons = NULL;
  }
}
