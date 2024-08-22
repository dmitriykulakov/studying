#ifndef MAIN_H
#define MAIN_H



typedef enum {
  Start = '\n',
  Pause = 'p',
  Terminate = 'q',
  Left = 68,
  Right = 67,
  Up = 65,
  Down = 66,
  Action = 32
} UserAction_t;

typedef enum {
  START = 0,
  PAUSE,
  SPAWN,
  MOVING,
  ROTATION,
  SHIFTING,
  REACH,
  ATACHING,
  GAMEOVER,
  WIN,
  EXIT_STATE
} state_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif
