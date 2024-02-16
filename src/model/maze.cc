#include "maze.h"

void s21::Maze::OpenFile(const std::string& file_name) {
  file_.open(file_name);
  if (file_.is_open()) {
    Parse();
    file_.close();
  } else {
    std::cerr << "Error opening file: " << file_name << std::endl;
  }
}


void s21::Maze::Parse() {
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

void s21::Maze::Generate(int rows, int cols) {
    rows_ = rows;
    cols_ = cols;

    maze_main_.resize(rows_, std::vector<unsigned int>(cols_, 0));
    maze_vertical_walls_.resize(rows_, std::vector<unsigned int>(cols_, 0));
    maze_horizontal_walls_.resize(rows_, std::vector<unsigned int>(cols_, 0));

    SetValuesToLine(0);
    for (int i = 0; i < rows_; ++i) {
        SetVerticalWalls(i);
        SetHorizontalWalls(i);
        SetNewRow(i);
    }

}

void s21::Maze::SetValuesToLine(int row) {
    static int value = 1;
    for (int i = 0; i < cols_; ++i) {
        if (maze_main_[row][i] == 0) {
            maze_main_[row][i] = value;
            ++value;
        }
    }
}

void s21::Maze::SetVerticalWalls(int row) {
     std::vector<unsigned int> random_line = GetRandomLine();
     for (int i = 0; i < cols_; ++i) {
        if (random_line[i] == 1) {
            maze_vertical_walls_[row][i] = 1;
        } else {
            if (maze_main_[row][i] == maze_main_[row][i + 1]) {
                maze_vertical_walls_[row][i] = 1;
            } else {
                MergingCells(row, maze_main_[row][i], maze_main_[row][i + 1]);
            }
        }
     }
}

void s21::Maze::SetHorizontalWalls(int row) {
     std::vector<unsigned int> random_line = GetRandomLine();
     for (int i = 0; i < cols_; ++i) {
        if (random_line[i] == 1) {
            if (FindNumberUnderscores(row, maze_main_[row][i]) > 1) {
                maze_horizontal_walls_[row][i] = 1;
            }
        }
     }
}


std::vector<unsigned int> s21::Maze::GetRandomLine() {
    std::vector<unsigned int> random_numbers;
    random_numbers.reserve(cols_);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(0, 1);
    
    for (int i = 0; i < cols_ - 1; ++i) {
        random_numbers.push_back(dis(gen));
    }
    random_numbers.push_back(1);
    return random_numbers;
}

void s21::Maze::MergingCells(int row, unsigned int set_now, unsigned int set_before) {
    for (int i = 0; i < cols_; ++i) {
        if (maze_main_[row][i] == set_before) {
            maze_main_[row][i] = set_now;
        }
    }
}

int s21::Maze::FindNumberUnderscores(int row, unsigned int set_now) {
    int count = 0;
    for (int i = 0; i < cols_; ++i) {
        if (maze_main_[row][i] == set_now && maze_horizontal_walls_[row][i] == 0) {
            ++count;
        }
    }
    return count;
}

void s21::Maze::SetNewRow(int row) {
    if (row == rows_ - 1) {
        for (int i = 0; i < cols_; ++i) {
            maze_horizontal_walls_[row][i] = 1;
            if (maze_main_[row][i] != maze_main_[row][i + 1]) {
                maze_vertical_walls_[row][i] = 0;
                if (i == cols_ - 1) maze_vertical_walls_[row][i] = 1;
                MergingCells(row, maze_main_[row][i], maze_main_[row][i + 1]);
            }
        }
    } else {
        maze_main_[row + 1] = maze_main_[row];
        for (int i = 0; i < cols_; ++i) {
            if (maze_horizontal_walls_[row][i] == 1) {
                maze_main_[row + 1][i] = 0;
            }
        }
        SetValuesToLine(row + 1);
    }
}
