#include "s21_brick_game_test.h"

TEST(BrickGame, BrickGame_test_1) {
  Model_s m_model;
  ASSERT_EQ(m_model.getStateModel(), START);
  m_model.userInput_s(Start, 1);
  ASSERT_EQ(m_model.getStateModel(), SHIFTING);
  m_model.userInput_s(Left, 1);
  ASSERT_EQ(m_model.getStateModel(), SHIFTING);
  m_model.userInput_s(Action, 1);
  m_model.userInput_s(Up, 1);
  ASSERT_EQ(m_model.getStateModel(), SHIFTING);
  m_model.userInput_s(Action, 1);
  m_model.userInput_s(Right, 1);
  m_model.userInput_s(Action, 1);
  ASSERT_EQ(m_model.getStateModel(), SHIFTING);
  m_model.userInput_s(Down, 1);
  ASSERT_EQ(m_model.getStateModel(), SHIFTING);
  m_model.userInput_s(Pause, 1);
  GameInfo_t tmp = m_model.updateCurrentState_s();
  ASSERT_EQ(tmp.pause, 1);
  m_model.userInput_s(Pause, 1);
  tmp = m_model.updateCurrentState_s();
  ASSERT_EQ(tmp.pause, 0);
  ASSERT_EQ(m_model.getStateModel(), SHIFTING);
  m_model.userInput_s(Action, 1);
  ASSERT_EQ(m_model.getStateModel(), SHIFTING);
  for (int i = 0; i < 11; i++) {
    m_model.userInput_s((UserAction_t)0, 0);
  }
  ASSERT_EQ(m_model.getStateModel(), SHIFTING);
  for (int i = 0; i < 20; i++) {
    m_model.userInput_s(Action, 1);
  }
  ASSERT_EQ(m_model.getStateModel(), GAMEOVER);
  m_model.userInput_s(Start, 1);
  ASSERT_EQ(m_model.getStateModel(), START);
  m_model.userInput_s(Start, 1);
  ASSERT_EQ(m_model.getStateModel(), SHIFTING);
  m_model.userInput_s(Terminate, 1);
}

TEST(BrickGame, BrickGame_test_2) {
  Model_s m_model;
  m_model.userInput_s(Start, 1);
  m_model.userInput_s(Right, 1);
  m_model.userInput_s(Down, 1);
  m_model.userInput_s(Left, 1);
  ASSERT_EQ(m_model.getStateModel(), GAMEOVER);
}

TEST(BrickGame, BrickGame_test_3) {
  Model_s m_model;
  m_model.writeHighScore(10);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
