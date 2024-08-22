#include "viever.h"

#include "ui_viever.h"

Viever::Viever(QWidget *parent) : QMainWindow(parent), ui(new Ui::Viever) {
  ui->setupUi(this);
  this->setFixedWidth(this->width());
  this->setFixedHeight(this->height());
  set_settings();
  ui->openGLWidget->show();
  connect(ui->pushButton_figure_color, SIGNAL(clicked()), this,
          SLOT(set_figure_color()));
  connect(ui->pushButton_background_color, SIGNAL(clicked()), this,
          SLOT(set_background_color()));
}

Viever::~Viever() { delete ui; }

void Viever::set_figure_color() {
  QString str{};
  if (set_color(&ui->openGLWidget->figure_color, &str)) {
    ui->pushButton_figure_color->setStyleSheet(str);
    ui->openGLWidget->update();
    change_settings();
  }
}

void Viever::set_background_color() {
  QString str{};
  if (set_color(&ui->openGLWidget->background_color, &str)) {
    ui->pushButton_background_color->setStyleSheet(str);
    ui->openGLWidget->update();
    change_settings();
  }
}

int Viever::set_color(struct color *color, QString *str) {
  int result = 0;
  QColor tmp{0, 0, 0};
  tmp = QColorDialog::getColor(tmp);
  color->red = tmp.red();
  color->green = tmp.green();
  color->blue = tmp.blue();
  set_button_color(*color, str);
  result = 1;
  return result;
}

void Viever::set_button_color(struct color color, QString *str) {
  *str = "background-color: rgb(";
  str->append(QString::number(color.red).append(",").append(
      QString::number(color.green)
          .append(",")
          .append(QString::number(color.blue))
          .append(")")));
}

void Viever::on_radioButton_central_pressed() {
  ui->openGLWidget->projection = 0;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_parallel_pressed() {
  ui->openGLWidget->projection = 1;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_solid_pressed() {
  ui->openGLWidget->edges = 0;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_dashed_pressed() {
  ui->openGLWidget->edges = 1;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_none_pressed() {
  ui->openGLWidget->vertexes = 0;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_circle_pressed() {
  ui->openGLWidget->vertexes = 1;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_square_pressed() {
  ui->openGLWidget->vertexes = 2;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_pushButton_apply_changes_clicked() {
  if (ui->openGLWidget->matrix_of_vertexes.matrix != nullptr) {
    move_figure(&ui->openGLWidget->matrix_of_vertexes,
                ui->doubleSpinBox_move_x->value(),
                ui->doubleSpinBox_move_y->value(),
                ui->doubleSpinBox_move_z->value());
    rotate_figure(&ui->openGLWidget->matrix_of_vertexes,
                  ui->doubleSpinBox_rotate_x->value(),
                  ui->doubleSpinBox_rotate_y->value(),
                  ui->doubleSpinBox_rotate_z->value());
    change_figure(&ui->openGLWidget->matrix_of_vertexes,
                  ui->doubleSpinBox_scale->value());
    ui->openGLWidget->update();
  }
}

void Viever::on_pushButton_open_choose_file_clicked() {
  QString filename1 =
      QFileDialog::getOpenFileName(0, "Открыть object file", "./Object_files");
  strcpy(ui->openGLWidget->filename, filename1.toLocal8Bit().data());
  if (ui->openGLWidget->function_result == 0)
    free_memory(&ui->openGLWidget->matrix_of_vertexes,
                &ui->openGLWidget->polygons,
                ui->openGLWidget->count.count_of_facets);
  ui->openGLWidget->count_edges = 0;
  ui->openGLWidget->function_result =
      parsing(ui->openGLWidget->filename, &ui->openGLWidget->count,
              &ui->openGLWidget->matrix_of_vertexes,
              &ui->openGLWidget->polygons, &ui->openGLWidget->count_edges);
  clean_changes();
  ui->openGLWidget->update();
  if (ui->openGLWidget->function_result == 0) {
    ui->label_open_result->setText("OK");
    ui->filename->setText((strrchr(ui->openGLWidget->filename, '/')) + 1);
    ui->vertexes_amount->setText(
        QString::number(ui->openGLWidget->count.count_of_vertexes - 1));
    ui->edges_amount_2->setText(QString::number(ui->openGLWidget->count_edges));
  } else {
    ui->filename->setText("");
    ui->vertexes_amount->setText("");
    strcpy(ui->openGLWidget->filename, "");
    ui->edges_amount_2->setText("");
    if (ui->openGLWidget->function_result == 1)
      ui->label_open_result->setText("Problem with memory, please try again");
    if (ui->openGLWidget->function_result == 2)
      ui->label_open_result->setText("The obj file is wrong");
    if (ui->openGLWidget->function_result == 3)
      ui->label_open_result->setText("The file does not exist");
    if (ui->openGLWidget->function_result == 4)
      ui->label_open_result->setText("The file is not .obj");
  }
}

void Viever::on_pushButton_exit_clicked() {
  free_memory(&ui->openGLWidget->matrix_of_vertexes,
              &ui->openGLWidget->polygons,
              ui->openGLWidget->count.count_of_facets);
  close();
  ui->openGLWidget->close();
}

void Viever::on_pushButton_clear_changes_clicked() {
  free_memory(&ui->openGLWidget->matrix_of_vertexes,
              &ui->openGLWidget->polygons,
              ui->openGLWidget->count.count_of_facets);
  parsing(ui->openGLWidget->filename, &ui->openGLWidget->count,
          &ui->openGLWidget->matrix_of_vertexes, &ui->openGLWidget->polygons,
          &ui->openGLWidget->count_edges);
  clean_changes();
  ui->openGLWidget->update();
}

void Viever::clean_changes() {
  ui->doubleSpinBox_move_x->setValue(0);
  ui->doubleSpinBox_move_y->setValue(0);
  ui->doubleSpinBox_move_z->setValue(0);
  ui->doubleSpinBox_rotate_x->setValue(0);
  ui->doubleSpinBox_rotate_y->setValue(0);
  ui->doubleSpinBox_rotate_z->setValue(0);
  ui->doubleSpinBox_scale->setValue(1);
  change_settings();
}

void Viever::on_doubleSpinBox_thikness_valueChanged(double arg1) {
  ui->openGLWidget->thickness = arg1;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_pushButton_bmp_clicked() {
  QFileDialog file_dailog(this);
  QDateTime date = QDateTime::currentDateTime();
  QString file_name = "Viewer_" + date.toString("yyyy.MM.dd_hh.mm.ss") + ".bmp";
  QString file_dialog_file_name = file_dailog.getSaveFileName(
      this, tr("Save image"), file_name, tr("image (*.bmp)"));
  QImage image = ui->openGLWidget->grabFramebuffer();
  image.save(file_name);
}

void Viever::on_pushButton_jpeg_clicked() {
  QFileDialog file_dailog(this);
  QDateTime date = QDateTime::currentDateTime();
  QString file_name =
      "Viewer_" + date.toString("yyyy.MM.dd_hh.mm.ss") + ".jpeg";
  QString file_dialog_file_name = file_dailog.getSaveFileName(
      this, tr("Save image"), file_name, tr("image (*.jpeg)"));
  QImage image = ui->openGLWidget->grabFramebuffer();
  image.save(file_name);
}

void Viever::on_pushButton_gif_clicked() {
  QDateTime current_date = QDateTime::currentDateTime();

  QFileDialog file_dailog(this);
  QDateTime date = QDateTime::currentDateTime();
  QString file_name = "Viewer_" + date.toString("yyyy.MM.dd_hh.mm.ss") + ".gif";
  QString file_dialog_file_name = file_dailog.getSaveFileName(
      this, tr("Save image"), file_name, tr("image (*.gif)"));
}

void Viever::change_settings() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");
  settings.setValue("ui->openGLWidget->figure_color.red = ",
                    ui->openGLWidget->figure_color.red);
  settings.setValue("ui->openGLWidget->figure_color.green = ",
                    ui->openGLWidget->figure_color.green);
  settings.setValue("ui->openGLWidget->figure_color.blue = ",
                    ui->openGLWidget->figure_color.blue);
  settings.setValue("ui->openGLWidget->background_color.red = ",
                    ui->openGLWidget->background_color.red);
  settings.setValue("ui->openGLWidget->background_color.green = ",
                    ui->openGLWidget->background_color.green);
  settings.setValue("ui->openGLWidget->background_color.blue = ",
                    ui->openGLWidget->background_color.blue);
  settings.setValue("edges = ", ui->openGLWidget->edges);
  settings.setValue("projection = ", ui->openGLWidget->projection);
  settings.setValue("vertexes = ", ui->openGLWidget->vertexes);
  settings.setValue("thickness = ", ui->openGLWidget->thickness);
  settings.endGroup();
}

void Viever::set_settings() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");
  ui->openGLWidget->figure_color.red =
      settings.value("ui->openGLWidget->figure_color.red = ").toInt();
  ui->openGLWidget->figure_color.green =
      settings.value("ui->openGLWidget->figure_color.green = ").toInt();
  ui->openGLWidget->figure_color.blue =
      settings.value("ui->openGLWidget->figure_color.blue = ").toInt();
  ui->openGLWidget->background_color.red =
      settings.value("ui->openGLWidget->background_color.red = ").toInt();
  ui->openGLWidget->background_color.green =
      settings.value("ui->openGLWidget->background_color.green = ").toInt();
  ui->openGLWidget->background_color.blue =
      settings.value("ui->openGLWidget->background_color.blue = ").toInt();
  QString figure_button_color, background_button_color;
  set_button_color(ui->openGLWidget->figure_color, &figure_button_color);
  set_button_color(ui->openGLWidget->background_color,
                   &background_button_color);
  ui->pushButton_background_color->setStyleSheet(background_button_color);
  ui->pushButton_figure_color->setStyleSheet(figure_button_color);
  ui->openGLWidget->edges = settings.value("edges = ").toInt();
  ui->openGLWidget->projection = settings.value("projection = ").toInt();
  ui->openGLWidget->vertexes = settings.value("vertexes = ").toInt();
  ui->openGLWidget->thickness = settings.value("thickness = ").toDouble();
  if (ui->openGLWidget->edges == 0) ui->radioButton_solid->setChecked(true);
  if (ui->openGLWidget->edges == 1) ui->radioButton_dashed->setChecked(true);
  if (ui->openGLWidget->vertexes == 0) ui->radioButton_none->setChecked(true);
  if (ui->openGLWidget->vertexes == 1) ui->radioButton_circle->setChecked(true);
  if (ui->openGLWidget->vertexes == 2) ui->radioButton_square->setChecked(true);
  if (ui->openGLWidget->projection == 0)
    ui->radioButton_central->setChecked(true);
  if (ui->openGLWidget->projection == 1)
    ui->radioButton_parallel->setChecked(true);
  ui->doubleSpinBox_thikness->setValue(ui->openGLWidget->thickness);
  settings.endGroup();
}
