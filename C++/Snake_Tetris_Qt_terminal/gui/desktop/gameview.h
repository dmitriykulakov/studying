#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>

#include "../../brick_game/main.h"
#include "../../brick_game/snake/controller_s.h"
#include "../../brick_game/snake/model_s.h"

extern "C" {
#include "../../brick_game/tetris/model.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class GameView;
}
QT_END_NAMESPACE

namespace s21 {

class GameView : public QMainWindow {
  Q_OBJECT

 public:
  GameView(QWidget *parent = nullptr);
  ~GameView();
  bool hold = 0;
  UserAction_t key_t = (UserAction_t)0;
  GameInfo_t banner;
  Figure_loc figure_;
  tmp_data Data;
  state_t state = START;
  int game = 0;
  Controller m_controller;

 protected:
  void keyPressEvent(QKeyEvent *e) override;
  void paintEvent(QPaintEvent *event) override;

 private slots:
  void slotTimerAlarm();
  void empty_data();
  void set_data();
  void print_field(QPainter *painter);

 private:
  Ui::GameView *ui;
  QTimer *timer;
};

};      // namespace s21
#endif  // GAMEVIEW_H
