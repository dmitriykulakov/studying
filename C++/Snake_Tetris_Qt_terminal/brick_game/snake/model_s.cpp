#include "model_s.h"

s21::Model_s::Model_s() {
  banner.field = new int*[23];
  for (int i{}; i < 23; i++) {
    banner.field[i] = new int[16];
  }
  banner.next = nullptr;
  banner.score = 0;
  std::string buffer;
  std::ifstream in("./high_score_snake.txt");
  std::getline(in, buffer);
  in.close();
  banner.high_score = std::stod(buffer);
  banner.level = 1;
  banner.speed = 1;
  banner.pause = 0;
}

s21::Model_s::~Model_s() {
  for (int i{}; i < 23; i++) delete[] banner.field[i];
  delete[] banner.field;
}

state_t s21::Model_s::getStateModel() { return state; }

GameInfo_t s21::Model_s::updateCurrentState_s() { return banner; }

void s21::Model_s::userInput_s(UserAction_t action, bool hold) {
  if (hold) apply_action_s(action);
  if (state == START) {
    snake.clear();
    clean_banner_s();
    snake.insert(snake.begin(), {8, 7});
    snake.insert(snake.begin(), {9, 7});
    snake.insert(snake.begin(), {10, 7});
    snake.insert(snake.begin(), {11, 7});
    for (int i{}; i < int(snake.size()); i++)
      banner.field[snake[i].Y][snake[i].X] = 1;
    direction = UP;
    count = 0;
  }
  if (state == SPAWN) spawn_function_s();
  if (state == REACH) shift_function_s();
  if (state == MOVING) move_function_s(action);
  if (state == PAUSE)
    banner.pause = 1;
  else
    banner.pause = 0;
  if (state == SHIFTING) {
    count++;
    if (count == 10) shift_function_s();
  }
}

void s21::Model_s::apply_action_s(UserAction_t action) {
  if (state != GAMEOVER && state != WIN) {
    if (state == START) {
      if (action == Start) state = SPAWN;
    } else if (action == Pause) {
      if (state != PAUSE)
        state = PAUSE;
      else
        state = SHIFTING;
    } else if (action == Left || action == Right || action == Down ||
               action == Up)
      state = MOVING;
    else if (action == Action)
      state = REACH;
  } else {
    if (action == Start) state = START;
  }
  if (action == Terminate) state = EXIT_STATE;
}

void s21::Model_s::clean_banner_s() {
  clean_banner_field();
  banner.score = 0;
  banner.level = 1;
  banner.speed = 1;
  banner.pause = 0;
}

void s21::Model_s::clean_banner_field() {
  for (int i = 0; i < 23; i++) {
    for (int j = 0; j < 16; j++) {
      banner.field[i][j] = 0;
    }
  }
}

void s21::Model_s::spawn_function_s() {
  int spawn = 1;
  while (spawn) {
    spawn = 0;
    apple.X = rand() % 10 + 3;
    apple.Y = rand() % 20;
    for (int i{}; i < (int)(snake.size()); i++) {
      if (snake[i].X == apple.X && snake[i].Y == apple.Y) spawn = 1;
    }
  }
  banner.field[apple.Y][apple.X] = 2;
  state = SHIFTING;
}

void s21::Model_s::move_function_s(UserAction_t action) {
  Position tmp;
  state = SHIFTING;
  int FLAG = 0;
  if (direction == UP || direction == DOWN) {
    if (action == Right) {
      tmp = {snake.back().Y, snake.back().X + 1};
      direction = RIGHT;
      FLAG = 1;
    }
    if (action == Left) {
      tmp = {snake.back().Y, snake.back().X - 1};
      direction = LEFT;
      FLAG = 1;
    }
  }
  if (direction == RIGHT || direction == LEFT) {
    if (action == Up) {
      tmp = {snake.back().Y - 1, snake.back().X};
      direction = UP;
      FLAG = 1;
    }
    if (action == Down) {
      tmp = {snake.back().Y + 1, snake.back().X};
      direction = DOWN;
      FLAG = 1;
    }
  }
  if (FLAG) {
    snake.emplace_back(tmp);
    checkSnake();
  }
}

void s21::Model_s::checkSnake() {
  state = SHIFTING;
  checkGameover();
  if (state != GAMEOVER) {
    banner.field[(snake.back()).Y][(snake.back()).X] = 1;
    if (snake.back().Y == apple.Y && snake.back().X == apple.X) {
      (banner.score)++;
      if (banner.score > banner.high_score) banner.high_score = banner.score;
      if (banner.level < 10) {
        banner.level = banner.score / 5 + 1;
        banner.speed = banner.level;
      }
      if (snake.size() < 200)
        state = SPAWN;
      else
        state = WIN;
    } else {
      banner.field[snake[0].Y][snake[0].X] = 0;
      snake.erase(snake.begin());
    }
    count = 0;
  }
}

void s21::Model_s::checkGameover() {
  if (snake.back().Y == -1 || snake.back().Y == 20 || snake.back().X == 2 ||
      snake.back().X == 13)
    state = GAMEOVER;
  for (int i{}; i < (int)(snake.size()) - 1 && state != GAMEOVER; i++) {
    if (snake[i].Y == snake.back().Y && snake[i].X == snake.back().X)
      state = GAMEOVER;
  }
}

void s21::Model_s::shift_function_s() {
  Position tmp;
  if (direction == UP) tmp = {snake.back().Y - 1, snake.back().X};
  if (direction == DOWN) tmp = {snake.back().Y + 1, snake.back().X};
  if (direction == RIGHT) tmp = {snake.back().Y, snake.back().X + 1};
  if (direction == LEFT) tmp = {snake.back().Y, snake.back().X - 1};
  snake.emplace_back(tmp);
  checkSnake();
}

void s21::Model_s::writeHighScore(int high_score) {
  std::string str = std::to_string(high_score);
  std::ofstream out;
  out.open("./high_score_snake.txt");
  out << str << std::endl;
  out.close();
}
