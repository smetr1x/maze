#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "../model/maze.h"

namespace s21 {

class Controller {
    public:
        Controller() = default;
        ~Controller() = default;
        
        void OpenMaze(const std::string& file_name);
        void GenerateMaze(int rows, int cols);
        Maze* getMaze();

    private:
        Maze* maze_;

};

} //namespace s21



#endif // CONTROLLER_CONTROLLER_H_



