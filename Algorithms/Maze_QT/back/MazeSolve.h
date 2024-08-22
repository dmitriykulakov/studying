#ifndef MAZE_SOLVE_H_
#define MAZE_SOLVE_H_

#include <iostream>
#include <vector>

class MazeSolve {
 public:
  void SetMaze(std::vector<std::vector<int>> matrixVerticals__,
               std::vector<std::vector<int>> matrixHorizontals__);
  std::vector<std::pair<int, int>> GetSolve(int x1, int y1, int x2, int y2);
  void Routing(std::vector<std::pair<int, int>> currentPath,
               std::pair<int, int> currentPoint);
  void Check(int x, int y, std::vector<std::pair<int, int>> tmp);

 private:
  int rows_ = 0;
  int cols_ = 0;
  int stop_ = 0;
  std::vector<std::vector<int>> matrixVerticals_;
  std::vector<std::vector<int>> matrixHorizontals_;
  std::pair<int, int> finishPoint_;
  std::vector<std::pair<int, int>> result_;
};

#endif
