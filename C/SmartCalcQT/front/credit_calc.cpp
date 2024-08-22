#include "credit_calc.h"

#include "../backend/s21_smart_calculator.h"
#include "ui_credit_calc.h"

credit_calc::credit_calc(QWidget *parent)
    : QWidget(parent), ui(new Ui::credit_calc) {
  ui->setupUi(this);
}

credit_calc::~credit_calc() { delete ui; }

void credit_calc::on_radioButton_pressed() {
  double overpayment, total_payment, month_payment;
  annuity(ui->total_sum->value(), (int)(ui->time->value()),
          ui->percent->value(), &overpayment, &total_payment, &month_payment);
  ui->overpayment->setText(QString::number(overpayment, 'g', 10));
  ui->total_payment->setText(QString::number(total_payment, 'g', 10));
  ui->month_payment->setText(QString::number(month_payment, 'g', 10));
}

void credit_calc::on_radioButton_2_pressed() {
  double overpayment, total_payment, month_payment;
  diff(ui->total_sum->value(), (int)(ui->time->value()), ui->percent->value(),
       &overpayment, &total_payment, &month_payment);
  ui->overpayment->setText(QString::number(overpayment, 'g', 10));
  ui->total_payment->setText(QString::number(total_payment, 'g', 10));
  ui->month_payment->setText(QString::number(month_payment, 'g', 10));
}
