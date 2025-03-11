//
// Created by osmi on 3/5/25.
//

#ifndef BOARD_H
#define BOARD_H


#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    bool current;
    bool next;
} Cell;

typedef struct {
    Cell **cells;
    int size;
} Board;

void free_cells(Cell **cells, int size) {
    for (int i = 0; i < size; i++) {
        free(cells[i]);
        cells[i] = NULL;
    }

    free(cells);
    cells = NULL;
}

Board init_board(int size, int spawn_probability) {
    srand(time(NULL));

    Cell **arr = malloc(size * sizeof(Cell *));
    for (int i = 0; i < size; ++i) {
        arr[i] = (Cell *) malloc(size * sizeof(Cell));
        for (int j = 0; j < size; ++j) {
            int num = rand() % 100 + 1;
            bool alive = num < spawn_probability;
            arr[i][j].current = alive;
        }
    }

    Board res = {arr, size};
    return  res;
}

int get_neighbors(Board* cell_board, int row, int col) {
    int size = cell_board->size;
    Cell **cells = cell_board->cells;

    int rmin = (row == 0) ? 0 : -1;
    int rmax = (row >= size-1) ? 0 : 1;
    int cmin = (col == 0) ? 0 : -1;
    int cmax = (col >= size-1) ? 0 : 1;

    int res = 0;

    for (int i = rmin; i <= rmax; ++i) {
        for (int j = cmin; j <= cmax; ++j) {
            if (i == 0 && j == 0) continue;
            res += cells[row+i][col+j].current;
        }
    }

    return res;
}

void tick(Board* cell_board) {
    Cell **cells = cell_board->cells;
    int size = cell_board->size;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int n = get_neighbors(cell_board, i, j);
            bool current = cells[i][j].current;

            bool next_cell = current && (n < 2 || n > 3) ? 0 :
                !current && n == 3 ? 1 :
                current;
            cells[i][j].next = next_cell;
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cells[i][j].current = cells[i][j].next;
        }
    }
}


#endif //BOARD_H
