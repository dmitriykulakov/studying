#include "MazeReader.h"

void MazeReader::ReadMatrices(const std::string& filename) {
  std::ifstream infile(filename);
  if (!infile) {
    throw std::string{"ERROR: Unable to open file"};
  }

  int rows, cols;
  infile >> rows >> cols;
  if (rows > 50 || cols > 50) {
    throw std::string{
        "ERROR: Incorrect the size of the maze, the size should be less "
        "50x50"};
  }
  height_ = rows;
  width_ = cols;

  matrixVerticals_.resize(rows, std::vector<int>(cols));
  matrixHorizontals_.resize(rows, std::vector<int>(cols));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      infile >> matrixVerticals_[i][j];
    }
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      infile >> matrixHorizontals_[i][j];
    }
  }
}

int MazeReader::GetRows() { return height_; }

int MazeReader::GetCols() { return width_; }

std::vector<std::vector<int>> MazeReader::GetHorizontal() {
  return matrixHorizontals_;
}

std::vector<std::vector<int>> MazeReader::GetVertical() {
  return matrixVerticals_;
}
