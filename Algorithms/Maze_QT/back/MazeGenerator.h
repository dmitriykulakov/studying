#ifndef MAZE_GENERATOR_H_
#define MAZE_GENERATOR_H_

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

class MazeGenerator {
 public:
  void GenerateEyllerMaze();
  MazeGenerator(int rows, int cols);
  void WriteMatricesToFile(const std::string& filename);
  std::vector<std::vector<int>> GetHorizontal();
  std::vector<std::vector<int>> GetVertical();

 private:
  int rows_;
  int cols_;
  std::vector<std::vector<int>> matrixVerticals_;
  std::vector<std::vector<int>> matrixHorizontals_;

  void GenerateRandomSet(std::vector<int>& randomSet);
  void UnionSet(std::vector<int>& numSet, int currInd);
  bool IfLeftOpenned(const std::vector<int> numSet, int index, int row);
  void CheckLastRow(std::vector<int>& numSet);
  void SetRightBar(std::vector<int>& numSet, int row);
  void SetBottomBar(std::vector<int>& numSet, int row);
  void SetNewRow(std::vector<int>& numSet, int row, int& increment);
};

#endif
