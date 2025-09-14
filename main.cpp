// Nicholas Guevara
// CS 315 Dr. Kooshesh
// Project 1 - Maze
// 9/10/2025

#include "Maze.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <maze-file>" << std::endl;
        return 1;
    }

    Maze inputMaze(argv[1]);

    inputMaze.findStartAndTarget();
    std::stack<Cell> solution = inputMaze.solve();

    std::cout << "Maze solution: " << std::endl << std::endl;
    inputMaze.print(solution);
    
    return 0;
}



/*
INPUT
A text file containing the maze as a grid of zeros (paths) and ones (walls).
The maze is surrounded by walls, except for two open cells representing the start and target points.
There are no spaces between digits.

OUTPUT
The maze printed in the same format as the input, except that zeros on the solution path are replaced by blank spaces.
If no path exists, the program outputs a message stating that no solution is possible.
*/
