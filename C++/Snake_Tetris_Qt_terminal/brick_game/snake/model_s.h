#ifndef MODEL_S_H
#define MODEL_S_H

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "../main.h"

namespace s21 {

typedef struct {
  int Y;
  int X;
} Position;

typedef enum {
  UP = 0,
  DOWN,
  LEFT,
  RIGHT,
} Direction_s;

class Model_s {
 private:
  GameInfo_t banner;
  state_t state = START;
  UserAction_t key = (UserAction_t)0;
  int count = 0;
  Position apple{0, 0};
  std::vector<Position> snake{{11, 7}, {10, 7}, {9, 7}, {8, 7}};
  Direction_s direction = UP;

 public:
  Model_s();
  ~Model_s();
  state_t getStateModel();
  GameInfo_t updateCurrentState_s();
  void userInput_s(UserAction_t action, bool hold);
  void apply_action_s(UserAction_t action);
  void clean_banner_s();
  void clean_banner_field();
  void spawn_function_s();
  void move_function_s(UserAction_t action);
  void checkSnake();
  void checkGameover();
  void shift_function_s();
  void writeHighScore(int high_score);
};

};  // namespace s21

#endif
