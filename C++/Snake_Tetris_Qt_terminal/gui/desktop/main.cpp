#include <QApplication>

#include "gameview.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  GameView w;
  w.show();
  return a.exec();
}
