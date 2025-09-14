#include "Maze.h"
#include <iostream>
#include <fstream>


Maze::Maze(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::vector<std::string> mazeData;
    std::string mazeRow;

    while (std::getline(inFile, mazeRow)) {
        mazeData.push_back(mazeRow);
    }

    inFile.close();

    //populate the mazeGrid member

    for (size_t i = 0; i < mazeData.size(); ++i) {
        std::vector<int> mazeRowInts;
        std::string row = mazeData[i];

        for (size_t j = 0; j < row.size(); ++j) {
            char c = row[j];
            if (c == '0') {
                mazeRowInts.push_back(0);
            }
            else if (c == '1') {
                mazeRowInts.push_back(1);
            }
            else {
                std::cerr << "Invalid character in maze: " << c << std::endl;
                return;
            }
        }

        mazeGrid.push_back(mazeRowInts);
    }

    rows = mazeGrid.size();

    if (rows > 0) {
        cols = mazeGrid[0].size();
    }
    else {
        cols = 0;
    }
}

void Maze::findStartAndTarget() {
    //locate start and target cells on the perimeter
    if (rows == 0 || cols == 0) {
        return;
    }
    bool startFound = false;

    //scan top boundary
    for (size_t j = 0; j < cols; ++j) {
        if (mazeGrid[0][j] == 0) {
            if (!startFound) {
                startCell = std::make_tuple(0, j);
                startFound = true;
            }
            else {
                targetCell = std::make_tuple(0, j);
            }
        }
    }

//scan left boundary
for (size_t i = 0; i < rows; ++i) {
    if (mazeGrid[i][0] == 0) {
        if (!startFound) {
            startCell = std::make_tuple(i, 0);
            startFound = true;
        }
        else {
            targetCell = std::make_tuple(i, 0);
        }
    }
}

//scan right boundary
for (size_t i = 0; i < rows; ++i) {
    if (mazeGrid[i][cols - 1] == 0) {
        if (!startFound) {
            startCell = std::make_tuple(i, cols - 1);
            startFound = true;
        }
        else {
            targetCell = std::make_tuple(i, cols - 1);
        }
    }
}

// scan bottom boundary
for (size_t j = 0; j < cols; ++j) {
    if (mazeGrid[rows - 1][j] == 0) {
        if (!startFound) {
            startCell = std::make_tuple(rows - 1, j);
            startFound = true;
        }
        else {
            targetCell = std::make_tuple(rows - 1, j);
        }
    }
}
}

std::stack<Cell> Maze::solve() {
    std::stack<Cell> solution;
    solution.push(startCell);

    std::vector<std::vector<bool>> explored(rows, std::vector<bool>(cols, false));
    explored[std::get<0>(startCell)][std::get<1>(startCell)] = true;

    //represent the moves
    std::vector<std::tuple<int, int>> moves(4);
    moves[0] = std::make_tuple(-1, 0); // up
    moves[1] = std::make_tuple(1, 0); // down
    moves[2] = std::make_tuple(0, -1); // left
    moves[3] = std::make_tuple(0, 1); // right 

    bool pathFound = false;

    while (!solution.empty() && !pathFound) {
        Cell current = solution.top();
        Cell nextCell;
        int curRow = std::get<0>(current);
        int curCol = std::get<1>(current);

        bool hasUnexplored = false;


        //check all adjacent cells
        for (size_t k = 0; k < moves.size() && !hasUnexplored; ++k) {
            int newRow = curRow + std::get<0>(moves[k]);
            int newCol = curCol + std::get<1>(moves[k]);

            //check boundaries
            if (newRow >= 0 && newRow < (int)rows && newCol >= 0 && newCol < (int)cols) {
                //if path cell and not explored
                if (mazeGrid[newRow][newCol] == 0 && !explored[newRow][newCol]) {
                    nextCell = std::make_tuple(newRow, newCol);
                    solution.push(nextCell);
                    explored[newRow][newCol] = true;
                    hasUnexplored = true;

                    //check if target
                    if (nextCell == targetCell) {
                        pathFound = true;
                    }
                }
            }
        }

        if (!hasUnexplored) {
            solution.pop();
        }
    }
    return solution;
}

void Maze::print(const std::stack<Cell>& solution) const {
    if (solution.empty()) {
        std::cout << "No solution is possible." << std::endl;
        return;
    }

    std::vector<std::vector<char>> displayGrid(rows, std::vector<char>(cols));

    //fill grid with 1 for wall and empty space for path
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (mazeGrid[i][j] == 0){
                displayGrid[i][j] = '0';
            }
            else {
                displayGrid[i][j] = '1';
            }
        }
    }

    // mark path in the grid
    std::stack<Cell> tempSolution = solution;

    while (!tempSolution.empty()) {
        Cell pathCell = tempSolution.top();
        tempSolution.pop();

        size_t row = std::get<0>(pathCell);
        size_t col = std::get<1>(pathCell);

        displayGrid[row][col] = '*';
    }
    // print the grid
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (displayGrid[i][j] == '*') {
                std::cout << "\033[31m*\033[0m"; // red
            }
            else {
                std::cout << displayGrid[i][j]; // walls or spaces
            }
        }
        std::cout << std::endl;
    }
}