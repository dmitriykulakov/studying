#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(int rows, int cols) : rows_(rows), cols_(cols) {
  matrixVerticals_.resize(rows, std::vector<int>(cols));
  matrixHorizontals_.resize(rows, std::vector<int>(cols));
};

void MazeGenerator::GenerateEyllerMaze() {
  srand(time(0));
  std::vector<int> numSet(cols_, 0);
  int increment = 0;
  for (int i = 0; i < cols_; ++i) {
    numSet[i] = ++increment;
  }
  for (int i = 0; i < rows_; ++i) {
    SetNewRow(numSet, i, increment);
    SetRightBar(numSet, i);
    SetBottomBar(numSet, i);
  }
}

void MazeGenerator::WriteMatricesToFile(const std::string& filename) {
  std::ofstream outfile(filename);
  if (!outfile) {
    throw std::string{"ERROR: the maze is not saved"};
  }

  outfile << rows_ << " " << cols_ << std::endl;

  for (const auto& row : matrixVerticals_) {
    for (size_t j = 0; j < row.size(); ++j) {
      outfile << row[j] << (j == row.size() - 1 ? "" : " ");
    }
    outfile << std::endl;
  }

  outfile << std::endl;

  for (const auto& row : matrixHorizontals_) {
    for (size_t j = 0; j < row.size(); ++j) {
      outfile << row[j] << (j == row.size() - 1 ? "" : " ");
    }
    outfile << std::endl;
  }
  outfile.close();
}

std::vector<std::vector<int>> MazeGenerator::GetHorizontal() {
  return matrixHorizontals_;
}

std::vector<std::vector<int>> MazeGenerator::GetVertical() {
  return matrixVerticals_;
}

void MazeGenerator::UnionSet(std::vector<int>& numSet, int currInd) {
  if (currInd < cols_ - 1) {
    int curNum = numSet[currInd];
    int nextNum = numSet[currInd + 1];
    for (int i = 0; i < cols_; ++i) {
      if (numSet[i] == nextNum) {
        numSet[i] = curNum;
      }
    }
  }
}

bool MazeGenerator::IfLeftOpenned(const std::vector<int> numSet, int index,
                                  int row) {
  int countOpen = 0;
  int curNum = numSet[index];
  for (int i = 0; i < cols_; ++i) {
    if (numSet[i] == curNum) {
      countOpen += matrixHorizontals_[row][i] == 0 ? 1 : 0;
    }
  }
  return countOpen >= 2;
}

void MazeGenerator::CheckLastRow(std::vector<int>& numSet) {
  for (int i = 0; i < cols_; ++i) {
    if ((i < cols_ - 1) && numSet[i] != numSet[i + 1]) {
      UnionSet(numSet, i);
      matrixVerticals_[rows_ - 1][i] = 0;
    }
  }
}

void MazeGenerator::SetRightBar(std::vector<int>& numSet, int row) {
  for (int i = 0; i < cols_; ++i) {
    if (i == cols_ - 1) {
      matrixVerticals_[row][i] = 1;
    } else if ((i < cols_ - 1) && numSet[i] == numSet[i + 1]) {
      matrixVerticals_[row][i] = 1;
    } else if (rand() % 2) {
      matrixVerticals_[row][i] = 1;
    } else {
      matrixVerticals_[row][i] = 0;
      UnionSet(numSet, i);
    }
  }
  if (row == rows_ - 1) {
    CheckLastRow(numSet);
    return;
  }
}

void MazeGenerator::SetBottomBar(std::vector<int>& numSet, int row) {
  for (int i = 0; i < cols_; ++i) {
    if (row == rows_ - 1) {
      matrixHorizontals_[row][i] = 1;
    } else if (rand() % 2) {
      matrixHorizontals_[row][i] = IfLeftOpenned(numSet, i, row) ? 1 : 0;
    } else {
      matrixHorizontals_[row][i] = 0;
    }
  }
}

void MazeGenerator::SetNewRow(std::vector<int>& numSet, int row,
                              int& increment) {
  if (row == 0) {
    return;
  }
  for (int i = 0; i < cols_; ++i) {
    if (matrixHorizontals_[row - 1][i] == 1) {
      numSet[i] = ++increment;
    }
  }
}
