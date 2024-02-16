#include "maze_open.h"

void s21::MazeOpen::OpenFile(const std::string& file_name) {
  file_.open(file_name);
  if (file_.is_open()) {
    Parse();
    file_.close();
  } else {
    std::cerr << "Error opening file: " << file_name << std::endl;
  }
}


void s21::MazeOpen::Parse() {
    file_ >> rows_ >> cols_;
    maze_vertical_walls_.resize(rows_, std::vector<unsigned int>(cols_));
    maze_horizontal_walls_.resize(rows_, std::vector<unsigned int>(cols_));

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            file_ >> maze_vertical_walls_[i][j];
        }
    }

    std::string empty_line;
    std::getline(file_, empty_line);

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            file_ >> maze_horizontal_walls_[i][j];
        }
    }
}


