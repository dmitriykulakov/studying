#ifndef MAZE_H
#define MAZE_H

#include <QFileDialog>
#include <QMainWindow>
#include <QPainter>
#include <iostream>

#include "../back/Maze.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Maze;
}
QT_END_NAMESPACE

class Maze : public QMainWindow {
  Q_OBJECT

 public:
  Maze(QWidget *parent = nullptr);
  int rows;
  int cols;
  bool solve;
  std::vector<std::vector<int>> matrixVerticals;
  std::vector<std::vector<int>> matrixHorizontals;
  std::vector<std::pair<int, int>> mazeSolve;
  bool paint;
  ~Maze();

 protected:
  void paintEvent(QPaintEvent *event) override;

 private slots:
  void on_Open_file_clicked();
  void on_mazeSolve_clicked();
  void on_mazeBuild_clicked();
  void clearErrors();

 private:
  Ui::Maze *ui;
};
#endif  // MAZE_H
