#ifndef MODEL_MAZE_GENERATE_H_
#define MODEL_MAZE_GENERATE_H_

#include <vector>
#include <random>
#include <iostream>

namespace s21 {

    using matrix = std::vector<std::vector<unsigned int>>;

class MazeGenerate {
    public:
    MazeGenerate() = default;
    ~MazeGenerate() = default;
    void Generate(int rows, int cols);

    int getRows() { return rows_; }
    int getCols() { return cols_; }
    matrix& getVerticalWalls() { return maze_vertical_walls_; }
    matrix& getHorizontalWalls() { return maze_horizontal_walls_; }

    private:
    int rows_{};
    int cols_{};
    matrix maze_main_{};
    matrix maze_vertical_walls_{};
    matrix maze_horizontal_walls_{};

    void SetValuesToLine(int row);
    void SetVerticalWalls(int row);
    void SetHorizontalWalls(int row);
    void SetNewRow(int row);

    std::vector<unsigned int> GetRandomLine();
    void MergingCells(int row, int set_now, int set_before);
    int FindNumberUnderscores(int row, int set_now);
};

} //namespace s21



#endif // MODEL_MAZE_GENERATE_H_
