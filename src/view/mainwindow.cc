#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
    mazeView_ = std::make_unique<MazeView>(ui_->graphicsView);
    setWindowTitle("Maze");
    setFixedSize(900, 670);

}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::on_open_maze_clicked() {
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file");
    mazeView_->LoadFile(file_name.toStdString());
}

void MainWindow::on_save_maze_clicked() {
    QString path = QFileDialog::getSaveFileName(this, "Save maze", QString(),
                                                  "Maze file (*.txt)");
    mazeView_->SaveFile(path.toStdString());
}

void MainWindow::on_generate_maze_clicked() {
    mazeView_->GenerateMaze(ui_->gen_rows->value(), ui_->gen_cols->value());
}

