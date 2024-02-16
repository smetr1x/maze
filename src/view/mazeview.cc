#include "mazeview.h"

MazeView::MazeView(QGraphicsView *parent) : QGraphicsView(parent) {
  scene_ = new QGraphicsScene(this);
  setFixedSize(610, 610);
  controller_ = std::make_unique<s21::Controller>();
}

MazeView::~MazeView() {
  delete scene_;
  scene_ = nullptr;
}

void MazeView::LoadFile(std::string file) {
    controller_->OpenMaze(file);
    rows_ = controller_->getMaze()->getRows();
    cols_ = controller_->getMaze()->getCols();
    vertical_walls_ = controller_->getMaze()->getVerticalWalls();
    horizontal_walls_ = controller_->getMaze()->getHorizontalWalls();
    DrawMaze();
}

void MazeView::ClearScene() {
  scene_->clear();
}

void MazeView::DrawMaze() {
  ClearScene();
  setScene(scene_);
  float cell_size_v = 600.0 / rows_;
  float cell_size_h = 600.0 / cols_;
  QPen wall_pen(Qt::white, 2);
  for (int row = 0; row < rows_; ++row) {
    for (int col = 0; col < cols_; ++col) {
      if (vertical_walls_[row][col] == 1) {
        scene_->addLine((col + 1) * cell_size_h, row * cell_size_v,
                        (col + 1) * cell_size_h, (row + 1) * cell_size_v,
                        wall_pen);
      }
    }
  }
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      if (horizontal_walls_[row][col] == 1) {
        scene_->addLine(col * cell_size_h, (row + 1) * cell_size_v,
                        (col + 1) * cell_size_h, (row + 1) * cell_size_v,
                        wall_pen);
      }
    }
  }
  scene_->addRect(0, 0, cols_ * cell_size_h, rows_ * cell_size_v, wall_pen);
}

void MazeView::SaveFile(std::string path_to_file) {
    std::ofstream file(path_to_file);
    if (file.is_open()) {
        file << rows_ << " " << cols_ << "\n";
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (j == cols_ - 1) {
                    file << vertical_walls_[i][j] << "\n";
                } else {
                    file << vertical_walls_[i][j] << " ";
                }
            }
        }

        file << "\n";

        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (j == cols_ - 1) {
                    file << horizontal_walls_[i][j] << "\n";
                } else {
                    file << horizontal_walls_[i][j] << " ";
                }
            }
        }

        file.close();
    } else {
        std::cerr << "Error saving data to file"<< std::endl;
    }
}

void MazeView::GenerateMaze(int rows, int cols) {
    controller_->GenerateMaze(rows, cols);
    rows_ = rows;
    cols_ = cols;
    vertical_walls_ = controller_->getMaze()->getVerticalWalls();
    horizontal_walls_ = controller_->getMaze()->getHorizontalWalls();
    DrawMaze();
}
