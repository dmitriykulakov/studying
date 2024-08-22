#include "maze.h"

#include "ui_maze.h"

Maze::Maze(QWidget *parent) : QMainWindow(parent), ui(new Ui::Maze) {
  ui->setupUi(this);
}

Maze::~Maze() { delete ui; }

void Maze::on_Open_file_clicked() {
  clearErrors();
  QString filename =
      QFileDialog::getOpenFileName(0, "Open a maze file", "../maze_samples");
  solve = 0;
  MazeReader reader;
  try {
    reader.ReadMatrices(qPrintable(filename));
    matrixHorizontals = reader.GetHorizontal();
    matrixVerticals = reader.GetVertical();
    rows = reader.GetRows();
    cols = reader.GetCols();
    paint = 1;
  } catch (std::string error_message) {
    paint = 0;
    ui->open_error->setText(QString::fromStdString(error_message));
  }
  repaint();
}

void Maze::on_mazeBuild_clicked() {
  clearErrors();
  try {
    rows = ui->rowsPerfectValue->value();
    cols = ui->colsPerfectValue->value();
    solve = 0;
    MazeGenerator generator(rows, cols);
    generator.GenerateEyllerMaze();
    generator.WriteMatricesToFile("generated_maze.txt");
    matrixHorizontals = generator.GetHorizontal();
    matrixVerticals = generator.GetVertical();
    paint = 1;
    ui->generate_result->setText(
        "The maze is saved in the file (generated_maze.txt)");
  } catch (std::string error_message) {
    paint = 0;
    solve = 0;
    ui->generate_result->setText(QString::fromStdString(error_message));
  }
  repaint();
}

void Maze::on_mazeSolve_clicked() {
  if (paint) {
    try {
      MazeSolve m;
      m.SetMaze(matrixVerticals, matrixHorizontals);
      ui->solve_error->setText("");
      mazeSolve =
          m.GetSolve(ui->x1_Value->value() - 1, ui->y1_Value->value() - 1,
                     ui->x2_Value->value() - 1, ui->y2_Value->value() - 1);
      solve = 1;
    } catch (std::string error_message) {
      solve = 0;
      ui->solve_error->setText(QString::fromStdString(error_message));
    }
  }
  repaint();
}

void Maze::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QPen pen(QColor(50, 50, 50));
  pen.setWidth(2);
  painter.setPen(pen);
  if (paint) {
    int size;
    if (rows > cols) {
      size = 500 / rows;
    } else {
      size = 500 / cols;
    }
    painter.fillRect(200, 200, size * cols, size * rows, QBrush{Qt::lightGray});
    painter.drawLine(200, 200, 200, 200 + size * rows);
    painter.drawLine(200, 200, 200 + size * cols, 200);
    for (int i = 0; i < int(matrixVerticals.size()); i++) {
      for (int j = 0; j < int(matrixVerticals[i].size()); j++) {
        if ((matrixVerticals[i])[j]) {
          painter.drawLine(200 + (j + 1) * size, 200 + i * size,
                           200 + (j + 1) * size, 200 + (i + 1) * size);
        }
      }
    }
    for (int i = 0; i < int(matrixHorizontals.size()); i++) {
      for (int j = 0; j < int(matrixHorizontals[i].size()); j++) {
        if ((matrixHorizontals[i])[j]) {
          painter.drawLine(200 + j * size, 200 + (i + 1) * size,
                           200 + (j + 1) * size, 200 + (i + 1) * size);
        }
      }
    }
    if (solve) {
      QPen pen(QColor(255, 0, 0));
      pen.setWidth(2);
      painter.setPen(pen);

      for (unsigned long i = 1; i < mazeSolve.size(); i++) {
        painter.drawLine(200 + size / 2 + size * (mazeSolve[i - 1].first),
                         200 + size / 2 + size * (mazeSolve[i - 1].second),
                         200 + size / 2 + size * (mazeSolve[i].first),
                         200 + size / 2 + size * (mazeSolve[i].second));
      }
      QRect circleStart(195 + size / 2 + size * ((*mazeSolve.begin()).first),
                        195 + size / 2 + size * ((*mazeSolve.begin()).second),
                        10, 10);
      QRect circleEnd(195 + size / 2 + size * ((*(mazeSolve.end() - 1)).first),
                      195 + size / 2 + size * ((*(mazeSolve.end() - 1)).second),
                      10, 10);
      painter.setBrush(QBrush(Qt::red));
      painter.drawEllipse(circleStart);
      painter.drawEllipse(circleEnd);
    }
  }
}

void Maze::clearErrors() {
  ui->open_error->setText("");
  ui->solve_error->setText("");
  ui->generate_result->setText("");
}
