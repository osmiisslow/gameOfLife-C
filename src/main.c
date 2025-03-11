//
// Created by osmi on 3/5/25.
//
#include <stdio.h>
#include <raylib.h>
#include "logic.h"

//size of the cellboard itself.
#define SIZE 100
//window width and height
#define WIDTH 800
#define HEIGHT 800

// helper function to draw the board, using raylib
void draw_board(Board *cell_board) {
    int size = cell_board->size;

    int cell_w = WIDTH / size;
    int cell_h = HEIGHT / size;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int x = cell_w * i;
            int y = cell_h * j;
            bool alive = cell_board->cells[i][j].current;

            Color cell_color = alive ? BLACK : WHITE;

            DrawRectangle(x, y, cell_w, cell_h, cell_color);
        }
    }
}


int main(void) {


    Board cell_board = init_board(SIZE, 25);


    InitWindow(WIDTH, HEIGHT, "Conway's Game of Life");

    SetTargetFPS(24);
    while (!WindowShouldClose()) {
        BeginDrawing();
        tick(&cell_board);
        draw_board(&cell_board);
        EndDrawing();
    }

    CloseWindow();
    //free the array that the board contains, because memory leaks fucking blow and I already made that mistake thrice now.
    free_cells(cell_board.cells, cell_board.size);

    return 0;
}

