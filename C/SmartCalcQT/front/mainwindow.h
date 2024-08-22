#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "credit_calc.h"

extern "C" {
#include "../backend/s21_smart_calculator.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  credit_calc *credit;
  int graph_status = 0;

 private slots:
  void simple_buttons_click();
  void function_buttons_click();
  void on_pushButton_equal_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_graph_clicked();
  void on_pushButton_clicked();
};
#endif  // MAINWINDOW_H
