#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <tuple>
#include <string>
#include <stack>


using Cell = std::tuple<size_t, size_t>;

class Maze {
public:
	Maze(const std::string& filename); //constructor
	void findStartAndTarget(); //mark start and target
	std::stack<Cell> solve(); //solve the maze
	void print(const std::stack<Cell>& solution = std::stack<Cell>()) const; // print the maze with solution

private:
	std::vector<std::vector<int>> mazeGrid;
	Cell startCell;
	Cell targetCell;
	size_t rows = 0;
	size_t cols = 0;
};

#endif