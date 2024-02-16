#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <memory>

#include "mazeview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_maze_clicked();
    void on_save_maze_clicked();
    void on_generate_maze_clicked();

private:
    Ui::MainWindow *ui_;
    std::unique_ptr<MazeView> mazeView_;

};

#endif // VIEW_MAINWINDOW_H
