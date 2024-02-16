#include "controller.h"

void s21::Controller::OpenMaze(const std::string& file_name) {
    maze_ = new Maze();
    maze_->OpenFile(file_name);
}

void s21::Controller::GenerateMaze(int rows, int cols) {
    maze_ = new Maze();
    maze_->Generate(rows, cols);
}

s21::Maze* s21::Controller::getMaze() { return maze_; }
