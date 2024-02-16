#ifndef MODEL_MAZE_H_
#define MODEL_MAZE_H_

#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace s21 {

    using matrix = std::vector<std::vector<unsigned int>>;

class Maze {
    public:
    Maze() = default;
    ~Maze() = default;

    void OpenFile(const std::string& file_name);
    void Generate(int rows, int cols);

    int getRows() { return rows_; }
    int getCols() { return cols_; }
    matrix& getVerticalWalls() { return maze_vertical_walls_; }
    matrix& getHorizontalWalls() { return maze_horizontal_walls_; }

    private:
    std::ifstream file_{};
    int rows_{};
    int cols_{};
    matrix maze_main_{};
    matrix maze_vertical_walls_{};
    matrix maze_horizontal_walls_{};

    void Parse();

    void SetValuesToLine(int row);
    void SetVerticalWalls(int row);
    void SetHorizontalWalls(int row);
    void SetNewRow(int row);
    std::vector<unsigned int> GetRandomLine();
    void MergingCells(int row, unsigned int set_now, unsigned int set_before);
    int FindNumberUnderscores(int row, unsigned int set_now);
};

} //namespace s21



#endif // MODEL_MAZE_H_
