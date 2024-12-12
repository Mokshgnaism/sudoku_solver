#include <iostream>
#include <vector>

using namespace std;

// Function to print the Sudoku board
void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if placing num in (row, col) is valid
bool isValid(const vector<vector<int>>& board, int row, int col, int num) {
    // Check the row
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) return false;
    }

    // Check the column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) return false;
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == num) return false;
        }
    }

    return true;
}

// Backtracking function to solve Sudoku
bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            // Find an empty cell
            if (board[row][col] == 0) {
                // Try numbers 1 to 9
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;

                        // Recur to check if this leads to a solution
                        if (solveSudoku(board)) {
                            return true;
                        }

                        // Backtrack if no solution is found
                        board[row][col] = 0;
                    }
                }
                return false; // If no valid number can be placed
            }
        }
    }
    return true; // If the board is complete, the puzzle is solved
}

// Function to input the Sudoku puzzle from the user
void inputSudoku(vector<vector<int>>& board) {
    cout << "Enter the Sudoku puzzle as 9 rows (9 digits per row, 0 for empty cells):" << endl;
    for (int i = 0; i < 9; i++) {
        string rowInput;
        cin >> rowInput;

        if (rowInput.length() != 9) {
            cout << "Invalid row input! Please enter exactly 9 digits for each row." << endl;
            return;
        }

        // Convert the string to integers and store in the board
        for (int j = 0; j < 9; j++) {
            board[i][j] = rowInput[j] - '0';  // Convert char to integer
        }
    }
}

int main() {
    vector<vector<int>> board(9, vector<int>(9, 0));

    // Get the input Sudoku puzzle
    inputSudoku(board);

    cout << "Initial Sudoku Puzzle:" << endl;
    printBoard(board);

    // Solve the Sudoku puzzle
    if (solveSudoku(board)) {
        cout << "\nSolved Sudoku Puzzle:" << endl;
        printBoard(board);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}
