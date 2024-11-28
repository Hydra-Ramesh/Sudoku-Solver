#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <climits>

class SudokuCell {
private:
    int value;
    bool isFixed;
    std::vector<int> candidates;

public:
    SudokuCell() : value(0), isFixed(false) { 
        resetCandidates(); 
    }

    void setValue(int val, bool fixed = false) {
        value = val;
        isFixed = fixed;
    }

    int getValue() const { return value; }
    bool isInitialCell() const { return isFixed; }

    void resetCandidates() {
        candidates.clear();
        for (int i = 1; i <= 9; ++i) 
            candidates.push_back(i);
    }
};

class DancingLinksSudokuSolver {
private:
    static const int SIZE = 9;
    static const int CELL_COUNT = SIZE * SIZE * SIZE;
    
    struct Node {
        Node* left;
        Node* right;
        Node* up;
        Node* down;
        int row, col;
        Node* columnHeader;
    };

    std::vector<std::vector<SudokuCell>> board;
    std::vector<Node*> headers;
    std::vector<std::vector<int>> solution;

    Node* createNode(int r, int c) {
        Node* node = new Node{};
        node->row = r;
        node->col = c;
        node->left = node->right = node->up = node->down = node;
        return node;
    }

    void linkNodes() {
        headers.resize(400, nullptr);
        
        for (int i = 0; i < 400; ++i) {
            headers[i] = createNode(0, i);
        }

        for (int i = 0; i < 400; ++i) {
            headers[i]->right = headers[(i + 1) % 400];
            headers[(i + 1) % 400]->left = headers[i];
        }
    }

    bool isSafe(int row, int col, int num) {
        // Check row
        for (int x = 0; x < SIZE; x++)
            if (board[row][x].getValue() == num)
                return false;

        // Check column
        for (int x = 0; x < SIZE; x++)
            if (board[x][col].getValue() == num)
                return false;

        // Check 3x3 box
        int boxRowStart = row - row % 3;
        int boxColStart = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[boxRowStart + i][boxColStart + j].getValue() == num)
                    return false;

        return true;
    }

    bool solveRecursive() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (board[row][col].getValue() == 0) {
                    for (int num = 1; num <= 9; num++) {
                        if (isSafe(row, col, num)) {
                            board[row][col].setValue(num);
                            
                            if (solveRecursive())
                                return true;
                            
                            board[row][col].setValue(0);
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

public:
    DancingLinksSudokuSolver() : 
        board(SIZE, std::vector<SudokuCell>(SIZE)) {}

    void inputBoard() {
        std::cout << "Enter Sudoku Puzzle (0 for empty cells):\n";
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                int val;
                std::cin >> val;
                if (val != 0) {
                    board[row][col].setValue(val, true);
                }
            }
        }
    }

    void displayBoard() {
        std::cout << "┌───────┬───────┬───────┐\n";
        for (int row = 0; row < SIZE; row++) {
            std::cout << "│ ";
            for (int col = 0; col < SIZE; col++) {
                int val = board[row][col].getValue();
                std::cout << (val == 0 ? "◦ " : std::to_string(val) + " ");

                if ((col + 1) % 3 == 0) std::cout << "│ ";
            }
            std::cout << "\n";
            if ((row + 1) % 3 == 0 && row < 8) 
                std::cout << "├───────┼───────┼───────┤\n";
        }
        std::cout << "└───────┴───────┴───────┘\n";
    }

    bool solveSudoku() {
        auto start = std::chrono::high_resolution_clock::now();
        
        linkNodes();
        bool result = solveRecursive();
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        if (result) {
            std::cout << "Solved Successfully! Time: " << duration.count() << " μs\n";
            displayBoard();
        } else {
            std::cout << "No Solution Found\n";
        }
        
        return result;
    }

    ~DancingLinksSudokuSolver() {
        for (auto header : headers) {
            delete header;
        }
    }
};

int main() {
    try {
        DancingLinksSudokuSolver solver;
        solver.inputBoard();
        std::cout << "Original Puzzle:\n";
        solver.displayBoard();
        solver.solveSudoku();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}