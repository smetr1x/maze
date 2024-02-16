#include "maze_generate.h"

void s21::MazeGenerate::Generate(int rows, int cols) {
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

void s21::MazeGenerate::SetValuesToLine(int row) {
    static int value = 1;
    for (int i = 0; i < cols_; ++i) {
        if (maze_main_[row][i] == 0) {
            maze_main_[row][i] = value;
            ++value;
        }
    }
}

void s21::MazeGenerate::SetVerticalWalls(int row) {
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

void s21::MazeGenerate::SetHorizontalWalls(int row) {
     std::vector<unsigned int> random_line = GetRandomLine();
     for (int i = 0; i < cols_; ++i) {
        if (random_line[i] == 1) {
            if (FindNumberUnderscores(row, maze_main_[row][i]) > 1) {
                maze_horizontal_walls_[row][i] = 1;
            }
        }
     }
}


std::vector<unsigned int> s21::MazeGenerate::GetRandomLine() {
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

void s21::MazeGenerate::MergingCells(int row, int set_now, int set_before) {
    for (int i = 0; i < cols_; ++i) {
        if (maze_main_[row][i] == set_before) {
            maze_main_[row][i] = set_now;
        }
    }
}

int s21::MazeGenerate::FindNumberUnderscores(int row, int set_now) {
    int count = 0;
    for (int i = 0; i < cols_; ++i) {
        if (maze_main_[row][i] == set_now && maze_horizontal_walls_[row][i] == 0) {
            ++count;
        }
    }
    return count;
}

void s21::MazeGenerate::SetNewRow(int row) {
    if (row == rows_ - 1) { //Если строка последняя
        for (int i = 0; i < cols_; ++i) {
            maze_horizontal_walls_[row][i] = 1;
            if (maze_main_[row][i] != maze_main_[row][i + 1]) {
                maze_vertical_walls_[row][i] = 0;
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
