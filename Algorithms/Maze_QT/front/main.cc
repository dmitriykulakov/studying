#include <QApplication>

#include "maze.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Maze w;
  w.show();
  return a.exec();
}
