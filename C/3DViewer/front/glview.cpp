#include "glview.h"

#include <GL/gl.h>
//#include <GL/glu.h>

void glView::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor((double)222 / 255, (double)221 / 255, (double)218 / 255, 255);
  glColor3d(53 / 255, (double)131 / 255, (double)228 / 255);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glView::paintGL() {
  glClearColor((double)background_color.red / 255,
               (double)background_color.green / 255,
               (double)background_color.blue / 255, 255);
  glColor3d((double)figure_color.red / 255, (double)figure_color.green / 255,
            (double)figure_color.blue / 255);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // ###################################################### Edges begin
  glLineWidth(thickness);

  if (edges == 0) {
    glDisable(GL_LINE_STIPPLE);
  } else if (edges == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
  }

  if (function_result == 0) {
    for (int i{1}; i < count.count_of_facets; i++) {
      glBegin(GL_LINE_LOOP);
      for (int j{0}; j < polygons[i].numbers_of_vertexes_in_facets; j++) {
        if (projection == 1) {
          glVertex3d(matrix_of_vertexes.matrix[polygons[i].vertexes[j]][0],
                     matrix_of_vertexes.matrix[polygons[i].vertexes[j]][1],
                     matrix_of_vertexes.matrix[polygons[i].vertexes[j]][2]);
        } else if (projection == 0) {
          glVertex4d(matrix_of_vertexes.matrix[polygons[i].vertexes[j]][0],
                     matrix_of_vertexes.matrix[polygons[i].vertexes[j]][1], 0,
                     1 + matrix_of_vertexes.matrix[polygons[i].vertexes[j]][2]);
        }
      }
      glEnd();
    }
    // ###################################################### Edges end

    // ###################################################### Vertices begin
    if (vertexes == 0) {
      glDisable(GL_POINT_SMOOTH);
      glPointSize(1);
    } else if (vertexes == 1) {
      glEnable(GL_POINT_SMOOTH);
      glPointSize(10);
    } else if (vertexes == 2) {
      glDisable(GL_POINT_SMOOTH);
      glPointSize(10);
    }

    glBegin(GL_POINTS);
    for (int i{1}; i < matrix_of_vertexes.rows; i++) {
      if (projection == 1) {
        glVertex3d(matrix_of_vertexes.matrix[i][0],
                   matrix_of_vertexes.matrix[i][1],
                   matrix_of_vertexes.matrix[i][2]);
      } else if (projection == 0) {
        glVertex4d(matrix_of_vertexes.matrix[i][0],
                   matrix_of_vertexes.matrix[i][1], 0,
                   1 + matrix_of_vertexes.matrix[i][2]);
      }
    }
    glEnd();
    // ###################################################### Vertices end
  }
}
