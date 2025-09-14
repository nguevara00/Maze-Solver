# Maze Solver Project

## Student Information
- Name: Nick Guevara
- Student ID: 002 85 1971
- Repository link: https://github.com/nguevara00/Maze-Solver

## Collaboration and Sources
This project is my own work.
Outside resources used: 
- ChatGPT was used to clarify concepts and help with syntax for namespaces, tuples, file input, command-line arguments, and type aliases. 
- ChatGPT was also used for debugging and catching typos, and double checking the project met all requirements. 
- I made the implementation decisions and wrote the code myself.

## Implementation Details
- **Data Structures**: vector< string> for the file data, vector<vector< int>> for the maze grid, tuple<size_t, size_t> containing ordered pair coordinates as "Cell"s, vector<vector< bool>> for marking explored cells, stack< Cell> for the solution path.
- **Algorithms**: The major algorithm used was the iterative stack-based backtracking algorithm provided in the project that we studied and practiced in the lab section. It explores each possible move from the current cell, pushing valid unexplored cells onto the stack and popping cells off the stack when no valid moves are possible. Explored cells are tracked to ensure the algorithm doesn't revisit already-explored positions. The solution stack contains each cell of the solution path in reverse order.
- Wall cells are represented by 1, path cells represented by 0, solution path cells represented as Red * using the ANSI escape sequence suggested in the lab. The red color was optional but I used it to improve visibility.
- Start and Target cells are detected by iteratively scanning the four perimeters of the maze. 


## Testing and Status
- Tested with provided input file maze0-1_input.txt
- Tested functionality by changing start and target cells in the maze.
- **Status**: The program correctly finds a path through the maze and displays the maze with the solution path shown. If no solution is found, a message is displayed. Works correctly for start and target on any boundary
- **Limitation**: The program will mark the first open boundary cell as start and the next open boundary cell as target. Open cells on the boundary are not checked after the first two are marked.
