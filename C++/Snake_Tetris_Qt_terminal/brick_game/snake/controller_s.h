#ifndef CONTROLLER_S_H
#define CONTROLLER_S_H

#include "model_s.h"

namespace s21 {

class Controller {
 private:
  Model_s m_model;

 public:
  void setKey(UserAction_t key_t, bool hold);
  state_t getState();
  GameInfo_t getBanner();
  void setHighScore(int high_score);
};

};  // namespace s21

#endif
