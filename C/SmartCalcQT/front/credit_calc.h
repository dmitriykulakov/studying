#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <QWidget>

extern "C" {
#include "../backend/s21_smart_calculator.h"
}

namespace Ui {
class credit_calc;
}

class credit_calc : public QWidget {
  Q_OBJECT

 public:
  explicit credit_calc(QWidget *parent = nullptr);
  ~credit_calc();

 private slots:
  void on_radioButton_pressed();

  void on_radioButton_2_pressed();

 private:
  Ui::credit_calc *ui;
};

#endif  // CREDIT_CALC_H
