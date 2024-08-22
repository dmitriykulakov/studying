#ifndef MAZE_READER_H_
#define MAZE_READER_H_

#include <fstream>
#include <iostream>
#include <vector>

class MazeReader {
 public:
  void ReadMatrices(const std::string& filename);
  int GetRows();
  int GetCols();
  std::vector<std::vector<int>> GetHorizontal();
  std::vector<std::vector<int>> GetVertical();

 private:
  int height_ = 0;
  int width_ = 0;
  std::vector<std::vector<int>> matrixVerticals_;
  std::vector<std::vector<int>> matrixHorizontals_;
};

#endif
