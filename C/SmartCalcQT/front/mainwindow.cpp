#include "mainwindow.h"

#include "../backend/s21_smart_calculator.h"
#include "credit_calc.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  credit = new credit_calc();
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_add, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_open_bracelet, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));
  connect(ui->pushButton_close_bracelet, SIGNAL(clicked()), this,
          SLOT(simple_buttons_click()));

  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(function_buttons_click()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(function_buttons_click()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(function_buttons_click()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(function_buttons_click()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(function_buttons_click()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(function_buttons_click()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(function_buttons_click()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(function_buttons_click()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(function_buttons_click()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::simple_buttons_click() {
  if (ui->formula_print->text().contains('=')) {
    ui->formula_print->setText(ui->result->text());
  }
  QPushButton *button = (QPushButton *)sender();
  QString new_formula;
  new_formula = ui->formula_print->text() + button->text();
  ui->formula_print->setText(new_formula);
}

void MainWindow::function_buttons_click() {
  if (ui->formula_print->text().contains('=')) {
    ui->formula_print->setText(ui->result->text());
  }
  QPushButton *button = (QPushButton *)sender();
  QString new_formula;
  if (button->text() == "√") {
    new_formula = ui->formula_print->text() + "sqrt(";
    ui->formula_print->setText(new_formula);
  } else {
    new_formula = ui->formula_print->text() + button->text() + "(";
    ui->formula_print->setText(new_formula);
  }
}

void MainWindow::on_pushButton_equal_clicked() {
  if (!(ui->formula_print->text().contains('='))) {
    QPushButton *button = (QPushButton *)sender();
    QString new_formula;
    new_formula = ui->formula_print->text() + button->text();
    ui->formula_print->setText(new_formula);
  }
  double result = 0.0;
  char str[5000] = "";
  QString string = ui->formula_print->text();
  strcpy(str, string.toLocal8Bit().constData());
  int error = smart_calculator_simple(str, ui->X->value(), &result);
  graph_status = 0;
  if (error == 0) {
    ui->result->setText(QString::number(result, 'g', 20));
    graph_status = 1;
  } else if (error == 1)
    ui->result->setText("ERROR: input is longer than 255 symbols");
  else if (error == 2)
    ui->result->setText("ERROR: syntax error");
  else if (error == 3)
    ui->result->setText("ERROR: need to close the bracelet");
  else if (error == 4)
    ui->result->setText("ERROR: before close the bracelet you need to open it");
}

void MainWindow::on_pushButton_clear_clicked() {
  ui->formula_print->setText("");
  ui->result->setText("0");
}

void MainWindow::on_pushButton_graph_clicked() {
  double xBegin, xEnd, h, X;
  QVector<double> x, y;
  ui->GRAPH->clearGraphs();
  xBegin = ui->X_min->value();
  xEnd = ui->X_max->value();
  h = (xEnd - xBegin) / 100;
  ui->GRAPH->xAxis->setRange(ui->X_min->value(), ui->X_max->value());
  ui->GRAPH->yAxis->setRange(ui->Y_min->value(), ui->Y_max->value());
  if (graph_status == 1) {
    for (X = xBegin; X < xEnd; X = X + h) {
      x.push_back(X);
      double result = 0;
      char str[5000] = "";
      QString string = ui->formula_print->text();
      strcpy(str, string.toLocal8Bit().constData());
      smart_calculator_simple(str, X, &result);
      y.push_back(result);
    }
    ui->GRAPH->addGraph();
    ui->GRAPH->graph(0)->addData(x, y);
    ui->GRAPH->replot();
  }
}

void MainWindow::on_pushButton_clicked() { credit->show(); }
