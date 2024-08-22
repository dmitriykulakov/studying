#include "maze_test.h"

TEST(MAZE, Maze_test_1) {
  MazeSolve m_maze;
  std::vector<std::vector<int>> matrixVerticals_ = {{1, 1, 1, 0, 1},
                                                    {0, 1, 0, 0, 1},
                                                    {0, 0, 1, 0, 1},
                                                    {1, 1, 0, 0, 1},
                                                    {0, 0, 0, 0, 1}};
  std::vector<std::vector<int>> matrixHorizontals_ = {{0, 0, 0, 1, 0},
                                                      {1, 0, 0, 1, 1},
                                                      {0, 0, 1, 1, 0},
                                                      {1, 0, 1, 0, 0},
                                                      {1, 1, 1, 1, 1}};
  m_maze.SetMaze(matrixVerticals_, matrixHorizontals_);
  std::vector<std::pair<int, int>> result = m_maze.GetSolve(0, 0, 2, 3);
  ASSERT_EQ(result[0].first, 0);
  ASSERT_EQ(result[0].second, 0);
  ASSERT_EQ(result[1].first, 0);
  ASSERT_EQ(result[1].second, 1);
  ASSERT_EQ(result[2].first, 1);
  ASSERT_EQ(result[2].second, 1);
  ASSERT_EQ(result[3].first, 1);
  ASSERT_EQ(result[3].second, 2);
  ASSERT_EQ(result[4].first, 1);
  ASSERT_EQ(result[4].second, 3);
  ASSERT_EQ(result[5].first, 1);
  ASSERT_EQ(result[5].second, 4);
  ASSERT_EQ(result[6].first, 2);
  ASSERT_EQ(result[6].second, 4);
  ASSERT_EQ(result[7].first, 3);
  ASSERT_EQ(result[7].second, 4);
  ASSERT_EQ(result[8].first, 3);
  ASSERT_EQ(result[8].second, 3);
  ASSERT_EQ(result[9].first, 2);
  ASSERT_EQ(result[9].second, 3);
}

TEST(MAZE, Maze_test_2) {
  MazeSolve m_maze;
  std::vector<std::vector<int>> matrixVerticals_ = {{1, 1, 1, 0, 1},
                                                    {0, 1, 0, 0, 1},
                                                    {0, 0, 1, 0, 1},
                                                    {1, 1, 0, 0, 1},
                                                    {0, 0, 0, 0, 1}};
  std::vector<std::vector<int>> matrixHorizontals_ = {{0, 0, 0, 1, 0},
                                                      {1, 0, 0, 1, 1},
                                                      {0, 0, 1, 1, 0},
                                                      {1, 0, 1, 0, 0},
                                                      {1, 1, 1, 1, 1}};
  m_maze.SetMaze(matrixVerticals_, matrixHorizontals_);
  std::string str1 = "ERROR: Incorrect point START, not in the maze";
  try {
    std::vector<std::pair<int, int>> result = m_maze.GetSolve(5, 0, 2, 3);
  } catch (std::string error_message) {
    ASSERT_EQ(str1, error_message);
  }
}

TEST(MAZE, Maze_test_3) {
  MazeSolve m_maze;
  std::vector<std::vector<int>> matrixVerticals_ = {{1, 1, 1, 0, 1},
                                                    {0, 1, 0, 0, 1},
                                                    {0, 0, 1, 0, 1},
                                                    {1, 1, 0, 0, 1},
                                                    {0, 0, 0, 0, 1}};
  std::vector<std::vector<int>> matrixHorizontals_ = {{0, 0, 0, 1, 0},
                                                      {1, 0, 0, 1, 1},
                                                      {0, 0, 1, 1, 0},
                                                      {1, 0, 1, 0, 0},
                                                      {1, 1, 1, 1, 1}};
  m_maze.SetMaze(matrixVerticals_, matrixHorizontals_);
  std::string str1 = "ERROR: Incorrect point FINISH, not in the maze";
  try {
    std::vector<std::pair<int, int>> result = m_maze.GetSolve(0, 0, 5, 3);
  } catch (std::string error_message) {
    ASSERT_EQ(str1, error_message);
  }
}

TEST(MAZE, Maze_test_4) {
  MazeSolve m_maze;
  std::vector<std::vector<int>> matrixVerticals_ = {
      {0, 1, 0, 1}, {0, 1, 0, 1}, {0, 1, 0, 1}, {0, 1, 0, 1}};
  std::vector<std::vector<int>> matrixHorizontals_ = {
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}};
  m_maze.SetMaze(matrixVerticals_, matrixHorizontals_);
  std::string str1 = "ERROR: There is no solve of the maze";
  try {
    std::vector<std::pair<int, int>> result = m_maze.GetSolve(0, 0, 3, 3);
  } catch (std::string error_message) {
    ASSERT_EQ(str1, error_message);
  }
}

TEST(MAZE, Maze_test_5) {
  MazeReader mazeReader;
  mazeReader.ReadMatrices("maze_samples/maze_4x4.txt");
  ASSERT_EQ(mazeReader.GetCols(), 4);
  ASSERT_EQ(mazeReader.GetCols(), 4);
  ASSERT_EQ(mazeReader.GetHorizontal()[3][3], 1);
}

TEST(MAZE, Maze_test_6) {
  MazeReader mazeReader;
  mazeReader.ReadMatrices("maze_samples/maze_20x20.txt");
  ASSERT_EQ(mazeReader.GetCols(), 20);
  ASSERT_EQ(mazeReader.GetCols(), 20);
  ASSERT_EQ(mazeReader.GetVertical()[0][19], 1);
  ASSERT_EQ(mazeReader.GetVertical()[19][18], 0);
  ASSERT_EQ(mazeReader.GetHorizontal()[5][5], 1);
  ASSERT_EQ(mazeReader.GetHorizontal()[19][19], 1);
}

TEST(MAZE, Maze_test_7) {
  MazeReader mazeReader;
  std::string str1 = "ERROR: Unable to open file";
  try {
    mazeReader.ReadMatrices("maze_samples/maze_0x0.txt");
  } catch (std::string error_message) {
    ASSERT_EQ(str1, error_message);
  }
}

TEST(MAZE, Maze_test_8) {
  MazeGenerator mazeGenerator(10, 10);
  mazeGenerator.GenerateEyllerMaze();
  ASSERT_EQ(mazeGenerator.GetHorizontal().size(), 10);
  ASSERT_EQ(mazeGenerator.GetVertical().size(), 10);

  mazeGenerator.WriteMatricesToFile("maze_samples/maze_10x10.txt");
  MazeReader mazeReader;
  mazeReader.ReadMatrices("maze_samples/maze_10x10.txt");
  ASSERT_EQ(mazeReader.GetCols(), 10);
  ASSERT_EQ(mazeReader.GetCols(), 10);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
