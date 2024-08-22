#include "controller_s.h"

#include "../main.h"

void s21::Controller::setKey(UserAction_t key_t, bool hold) {
  m_model.userInput_s(key_t, hold);
}

state_t s21::Controller::getState() { return m_model.getStateModel(); }

GameInfo_t s21::Controller::getBanner() {
  return m_model.updateCurrentState_s();
}

void s21::Controller::setHighScore(int high_score) {
  m_model.writeHighScore(high_score);
}
