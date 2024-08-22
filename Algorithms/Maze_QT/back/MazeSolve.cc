#include "MazeSolve.h"

void MazeSolve::SetMaze(std::vector<std::vector<int>> matrixVerticals__,
                        std::vector<std::vector<int>> matrixHorizontals__) {
  matrixVerticals_ = matrixVerticals__;
  matrixHorizontals_ = matrixHorizontals__;
  rows_ = matrixVerticals_.size();
  cols_ = matrixVerticals_[0].size();
}

std::vector<std::pair<int, int>> MazeSolve::GetSolve(int x1, int y1, int x2,
                                                     int y2) {
  if (x1 >= cols_ || y1 >= rows_) {
    throw std::string{"ERROR: Incorrect point START, not in the maze"};
  }
  if (x2 >= cols_ || y2 >= rows_) {
    throw std::string{"ERROR: Incorrect point FINISH, not in the maze"};
  }
  finishPoint_ = {x2, y2};
  std::vector<std::pair<int, int>> tmp;
  Routing(tmp, {x1, y1});
  if (result_.size() == 0) {
    throw std::string{"ERROR: There is no solve of the maze"};
  }
  return result_;
}

void MazeSolve::Routing(std::vector<std::pair<int, int>> currentPath,
                        std::pair<int, int> currentPoint) {
  std::vector<std::pair<int, int>> tmp = currentPath;
  tmp.emplace_back(currentPoint);
  if (currentPoint.first == finishPoint_.first &&
      currentPoint.second == finishPoint_.second) {
    result_ = tmp;
    stop_ = 1;
  } else if (!stop_) {
    if (currentPoint.first) {
      if (matrixVerticals_[currentPoint.second][currentPoint.first - 1] == 0) {
        Check(currentPoint.first - 1, currentPoint.second, tmp);
      }
    }
    if (currentPoint.second) {
      if (matrixHorizontals_[currentPoint.second - 1][currentPoint.first] ==
          0) {
        Check(currentPoint.first, currentPoint.second - 1, tmp);
      }
    }
    if (matrixHorizontals_[currentPoint.second][currentPoint.first] == 0) {
      Check(currentPoint.first, currentPoint.second + 1, tmp);
    }
    if (matrixVerticals_[currentPoint.second][currentPoint.first] == 0) {
      Check(currentPoint.first + 1, currentPoint.second, tmp);
    }
  }
}

void MazeSolve::Check(int x, int y, std::vector<std::pair<int, int>> tmp) {
  int FLAG = 1;
  for (int i = 0; i < int(tmp.size()) && FLAG; i++) {
    if (tmp[i].first == x && tmp[i].second == y) {
      FLAG = 0;
    }
  }
  if (FLAG) {
    std::vector<std::pair<int, int>> tmp2 = tmp;
    Routing(tmp2, {x, y});
  }
}