## **Sudoku Solver Documentation**

### **Overview**
This program solves a Sudoku puzzle using a combination of **backtracking** and partial setup for the **Dancing Links (DLX)** algorithm. However, only backtracking is implemented for solving, while the dancing links structure is initialized but not utilized.

---

### **Key Components**
#### 1. **SudokuCell Class**
- Represents a single cell in the Sudoku grid.
- **Attributes:**
  - `value`: Holds the current value (0 for empty cells).
  - `isFixed`: Indicates if the value is pre-filled (immutable).
  - `candidates`: Stores possible values (1–9) for the cell.
- **Methods:**
  - `setValue(int val, bool fixed = false)`: Sets the cell's value and marks it as fixed if needed.
  - `getValue()`: Returns the current value.
  - `resetCandidates()`: Resets candidates to all possible values (1–9).

#### 2. **DancingLinksSudokuSolver Class**
- Implements the Sudoku solving logic.
- **Attributes:**
  - `board`: 9x9 grid of `SudokuCell` objects.
  - `headers`: Stores dancing links column headers (400 constraints for rows, columns, boxes, and numbers).
  - `solution`: Stores the solved Sudoku grid.

---

### **Core Methods**
#### a) **`inputBoard()`**
- Reads the initial Sudoku puzzle from the user.
- `0` indicates an empty cell.
- Pre-filled values are marked as fixed using `setValue()`.

#### b) **`displayBoard()`**
- Prints the current board in a user-friendly format with grid separators.

#### c) **`isSafe(int row, int col, int num)`**
- Checks if a number can safely be placed in a cell by ensuring:
  - It doesn’t exist in the same row.
  - It doesn’t exist in the same column.
  - It doesn’t exist in the 3x3 subgrid.

#### d) **`solveRecursive()`**
- Implements **backtracking** to solve the puzzle:
  - Finds the first empty cell.
  - Tries placing numbers (1–9) if they are safe.
  - Recursively solves the rest of the grid.
  - Backtracks if no valid placement exists.

#### e) **`linkNodes()`**
- Sets up the nodes required for the Dancing Links (DLX) structure.
- **Purpose**: Initializes a linked structure with column headers to track constraints.
- **Note**: This method is incomplete and unused in the actual solving process.

#### f) **`solveSudoku()`**
- Integrates the solving process:
  - Initializes dancing links (not used later).
  - Uses `solveRecursive()` to solve via backtracking.
  - Measures execution time.
  - Displays the solved board or a failure message.

---

### **Execution Flow**
1. **Input**: User provides a Sudoku puzzle with 0 for empty cells.
2. **Display**: Prints the original puzzle.
3. **Solve**: Solves the puzzle using backtracking.
4. **Output**:
   - If solved: Prints the solution and the time taken.
   - If unsolvable: Displays a failure message.

---

### **Important Notes**
1. **Dancing Links Setup**: 
   - Nodes are created and linked but never used in the solving process.
   - To fully implement DLX, constraint satisfaction must replace the backtracking approach.

2. **Performance**:
   - Backtracking is simple but not the most efficient for large constraint-solving problems.
   - DLX is significantly faster but requires proper integration.

3. **Input Assumptions**:
   - Input is a valid 9x9 Sudoku puzzle.
   - Conflicts in the initial setup (e.g., duplicate numbers in rows/columns) are not handled.

---

### **Sample Input/Output**
#### Input:
```
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
```

#### Output:
```
Original Puzzle:
┌───────┬───────┬───────┐
│ 5 3 ◦ │ ◦ 7 ◦ │ ◦ ◦ ◦ │
│ 6 ◦ ◦ │ 1 9 5 │ ◦ ◦ ◦ │
│ ◦ 9 8 │ ◦ ◦ ◦ │ ◦ 6 ◦ │
├───────┼───────┼───────┤
│ 8 ◦ ◦ │ ◦ 6 ◦ │ ◦ ◦ 3 │
│ 4 ◦ ◦ │ 8 ◦ 3 │ ◦ ◦ 1 │
│ 7 ◦ ◦ │ ◦ 2 ◦ │ ◦ ◦ 6 │
├───────┼───────┼───────┤
│ ◦ 6 ◦ │ ◦ ◦ ◦ │ 2 8 ◦ │
│ ◦ ◦ ◦ │ 4 1 9 │ ◦ ◦ 5 │
│ ◦ ◦ ◦ │ ◦ 8 ◦ │ ◦ 7 9 │
└───────┴───────┴───────┘

Solved Successfully! Time: 300 μs
┌───────┬───────┬───────┐
│ 5 3 4 │ 6 7 8 │ 9 1 2 │
│ 6 7 2 │ 1 9 5 │ 3 4 8 │
│ 1 9 8 │ 3 4 2 │ 5 6 7 │
├───────┼───────┼───────┤
│ 8 5 9 │ 7 6 1 │ 4 2 3 │
│ 4 2 6 │ 8 5 3 │ 7 9 1 │
│ 7 1 3 │ 9 2 4 │ 8 5 6 │
├───────┼───────┼───────┤
│ 9 6 1 │ 5 3 7 │ 2 8 4 │
│ 2 8 7 │ 4 1 9 │ 6 3 5 │
│ 3 4 5 │ 2 8 6 │ 1 7 9 │
└───────┴───────┴───────┘
```

---

### **Future Improvements**
1. Complete the Dancing Links (DLX) algorithm.
2. Add input validation for the initial board.
3. Optimize the backtracking by maintaining dynamic candidate lists.
