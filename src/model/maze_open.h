#ifndef MODEL_MAZE_OPEN_H_
#define MODEL_MAZE_OPEN_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

namespace s21 {

    using matrix = std::vector<std::vector<unsigned int>>;

class MazeOpen {
    public:
    MazeOpen() = default;
    ~MazeOpen() = default;
    void OpenFile(const std::string& file_name);

    int getRows() { return rows_; }
    int getCols() { return cols_; }
    matrix& getVerticalWalls() { return maze_vertical_walls_; }
    matrix& getHorizontalWalls() { return maze_horizontal_walls_; }

    private:
    std::ifstream file_{};
    int rows_{};
    int cols_{};
    matrix maze_vertical_walls_{};
    matrix maze_horizontal_walls_{};

    void Parse();

};

} //namespace s21



#endif // MODEL_MAZE_OPEN_H_
