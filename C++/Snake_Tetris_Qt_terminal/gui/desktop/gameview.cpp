#include "gameview.h"

#include "ui_gameview.h"

s21::GameView::GameView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GameView) {
  ui->setupUi(this);
  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
  timer->start(80 - banner.speed * 6);
  srand(time(NULL));
}

s21::GameView::~GameView() { delete ui; }

void s21::GameView::slotTimerAlarm() {
  if (game) {
    timer->start(80 - banner.speed * 6);
    if (state == EXIT_STATE) {
    if (game == 1) {
      write_high_score(banner.high_score);
      free_memory(Data.tmp_figure, banner.next, figure_.figure,
                  Data.only_field, banner.field);
    }
    if (game == 2) m_controller.setHighScore(banner.high_score);
    close();
  }
    if (state != SPAWN) {
      if (key_t)
        hold = 1;
      else {
        hold = 0;
      }
    } else
      key_t = (UserAction_t)0;

    if (game == 1)
      userInput(key_t, hold);
    else
      m_controller.setKey(key_t, hold);
    repaint();
    key_t = (UserAction_t)0;
    if (game == 2) state = m_controller.getState();
  }
}

void s21::GameView::keyPressEvent(QKeyEvent *e) {
  if (game == 0) {
    if (e->key() == Qt::Key_1) {
      game = 1;
      banner = create_banner();
      figure_ = create_figure();
      Data = create_Data();
      if (figure_.figure && Data.tmp_figure && banner.next && banner.field &&
          Data.only_field) {
        change_info(&banner);
        change_figure(&figure_);
        change_data((&Data));
        change_state(&state);
      } else
        close();
    }
    if (e->key() == Qt::Key_2) game = 2;
    if (e->key() == Qt::Key_Q) close();
  } else {
    if (e->key() == Qt::Key_Down) key_t = Down;
    if (e->key() == 83) key_t = Start;
    if (e->key() == Qt::Key_Down) key_t = Down;
    if (e->key() == Qt::Key_Up) key_t = Up;
    if (e->key() == Qt::Key_Left) key_t = Left;
    if (e->key() == Qt::Key_Right) key_t = Right;
    if (e->key() == Qt::Key_P) key_t = Pause;
    if (e->key() == Qt::Key_Q) key_t = Terminate;
    if (e->key() == 32) key_t = Action;
  }
}

void s21::GameView::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QBrush brush(Qt::green, Qt::SolidPattern);
  painter.setBrush(brush);
  QPen pen(QColor(50, 50, 50));
  pen.setWidth(3);
  painter.setPen(pen);
  if (game == 0)
    ui->label->setText(
        "PRESS:\n    1 - TO PLAY TETRIS\n    2 - TO PLAY SNAKE ");
  else {
    if (game == 2) banner = m_controller.getBanner();
    empty_data();
    if (state == START) ui->label->setText("PRESS S TO START THE GAME");
    if (state == PAUSE)
      ui->label_pause->setText("PAUSE");
    else
      ui->label_pause->setText("");
    if (state == GAMEOVER)
      ui->label->setText(
          "GAMEOVER\n\n PRESS S to try AGAIN\n\n PRESS Q to EXIT");
    if (state == WIN)
      ui->label->setText(
          "YOU ARE THE WINNER\n\n PRESS S to try AGAIN\n\n PRESS Q to EXIT");
    if (state != GAMEOVER && state != WIN && state != START &&
        state != EXIT_STATE) {
      set_data();
      print_field(&painter);
    }
  }
}

void s21::GameView::empty_data() {
  ui->label_level_sign->setText("");
  ui->label_level_value->setText("");
  ui->label_speed_sign->setText("");
  ui->label_speed_value->setText("");
  ui->label_score_sign->setText("");
  ui->label_score_value->setText("");
  ui->label_high_score_sign->setText("");
  ui->label_high_score_value->setText("");
  ui->label_next_sign->setText("");
}

void s21::GameView::set_data() {
  ui->label->setText("");
  ui->label_level_sign->setText("LEVEL");
  ui->label_level_value->setText(QString::number(banner.level));
  ui->label_speed_sign->setText("SPEED");
  ui->label_speed_value->setText(QString::number(banner.speed));
  ui->label_score_sign->setText("SCORE");
  ui->label_score_value->setText(QString::number(banner.score));
  ui->label_high_score_sign->setText("HIGH SCORE");
  ui->label_high_score_value->setText(QString::number(banner.high_score));
}

void s21::GameView::print_field(QPainter *painter) {
  for (int i = 0; i < 20; i++) {
    for (int j = 3; j < 13; j++) {
      if (banner.field[i][j] == 1) {
        QBrush brush(Qt::green, Qt::SolidPattern);
        painter->setBrush(brush);
        painter->drawRect(j * 20 + 51, i * 20 + 51, 20, 20);
      }
      if (banner.field[i][j] == 2) {
        QBrush brush(Qt::red, Qt::SolidPattern);
        painter->setBrush(brush);
        painter->drawRect(j * 20 + 51, i * 20 + 51, 20, 20);
      }
    }
  }
  if (game == 1) {
    ui->label_next_sign->setText("NEXT FIGURE");
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (banner.next[i][j] == 1)
          painter->drawRect(j * 20 + 351, i * 20 + 231, 20, 20);
      }
    }
  }
  painter->drawLine(110, 50, 110, 451);
  painter->drawLine(110, 451, 311, 451);
  painter->drawLine(311, 451, 311, 50);
  painter->drawLine(311, 50, 110, 50);
}
