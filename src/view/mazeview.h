#ifndef VIEW_MAZEVIEW_H
#define VIEW_MAZEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "../controller/controller.h"

class MazeView : public QGraphicsView {
    Q_OBJECT

public:
    MazeView(QGraphicsView *parent = nullptr);
    ~MazeView();

    void LoadFile(std::string file);
    void SaveFile(std::string path_to_file);
    void GenerateMaze(int rows, int cols);

private:
    QGraphicsScene *scene_;
    std::unique_ptr<s21::Controller> controller_;

    void DrawMaze();
    void ClearScene();

    int rows_{};
    int cols_{};
    s21::matrix vertical_walls_{};
    s21::matrix horizontal_walls_{};

};

#endif // VIEW_MAZEVIEW_H
