#ifndef GLVIEW_H
#define GLVIEW_H

#include <GL/gl.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <iostream>

#include "viever.h"

extern "C" {
#include "../backend/parsing.h"
}

typedef struct color {
  int red;
  int green;
  int blue;
} color;

class glView : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  explicit glView(QWidget *parent) : QOpenGLWidget(parent) {}

  glView();
  int function_result{5};
  char filename[1024] = "";
  data_t count;
  matrix_t matrix_of_vertexes{nullptr, 0, 0};
  polygon_t *polygons{nullptr};
  int count_edges;
  color figure_color;
  color background_color;
  int projection;
  int edges;
  int vertexes;
  double thickness;

 protected:
  void initializeGL() override;
  void paintGL() override;
};

#endif  // GLVIEW_H
