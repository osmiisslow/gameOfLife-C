//
// Created by osmi on 3/5/25.
//

#ifndef BOARD_H
#define BOARD_H


#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// A cell with a current state and a state of what it should be in the following generation.
typedef struct {
    bool current;
    bool next;
} Cell;

// a board with a size linked to it.
typedef struct {
    Cell **cells;
    int size;
} Board;

// bad news. I only freed the memory allocation for the outer array, not the remaining
// 100 or so additional mallocs. This caused a major memory leak. Good thinking, osmi.
void free_cells(Cell **cells, int size) {
    for (int i = 0; i < size; i++) {
        free(cells[i]);
        cells[i] = NULL;
    }

    free(cells);
    cells = NULL;
}

// make a board by setting each cell to either alive or not, depending on random number generation
Board init_board(int size, int spawn_probability) {
    srand(time(NULL));

    Cell **arr = malloc(size * sizeof(Cell *));
    for (int i = 0; i < size; ++i) {
        arr[i] = (Cell *) malloc(size * sizeof(Cell));
        for (int j = 0; j < size; ++j) {
            // generate a random number between 1 and 100
            int num = rand() % 100 + 1;
            // spawn probability passed by the user
            bool alive = num < spawn_probability;
            arr[i][j].current = alive;
        }
    }

    Board res = {arr, size};
    return  res;
}

// get the amount of alive neighbors of a given cell by counting the alive cells in a surrounding 3x3 sub array
int get_neighbors(Board* cell_board, int row, int col) {
    int size = cell_board->size;
    Cell **cells = cell_board->cells;

    // if the cell being checked is on any edge of the cell board, let's make sure it doesn't go out of bounds.
    int rmin = (row == 0) ? 0 : -1;
    int rmax = (row >= size-1) ? 0 : 1;
    int cmin = (col == 0) ? 0 : -1;
    int cmax = (col >= size-1) ? 0 : 1;

    int res = 0;

    // actually counts the alive cells.
    for (int i = rmin; i <= rmax; ++i) {
        for (int j = cmin; j <= cmax; ++j) {
            // skips the cell that's actually being checked.
            // otherwise the cell itself would also count itself as a neighbor.
            // that's plain wrong.
            if (i == 0 && j == 0) continue;
            res += cells[row+i][col+j].current;
        }
    }

    return res;
}

// applies the rules of conway's game of life to the board, and updates it.
void tick(Board* cell_board) {
    Cell **cells = cell_board->cells;
    int size = cell_board->size;

    // iterates through all cells on the board.
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // gets the neighbors of the current cell
            int n = get_neighbors(cell_board, i, j);
            bool current = cells[i][j].current;

            bool next_cell = current && (n < 2 || n > 3) ? 0 :
                !current && n == 3 ? 1 :
                current;

            // instead of making a whole another 2d array, which is like 6 fucking MB or some shit(10k elements! gee whiz!)
            // I made a struct containing a cell's current state and what it should be in the next generation
            // This is because if I switch the cell prematurely, it then fucks with everything else on the board
            // and this is the best idea I can come up with at the moment. Huzzah!
            cells[i][j].next = next_cell;
        }
    }

    // update the current state of the cells
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cells[i][j].current = cells[i][j].next;
        }
    }
}


#endif //BOARD_H
