//
// Created by osmi on 3/5/25.
//
#include <stdio.h>
#include <raylib.h>
#include "logic.h"

#define SIZE 100
#define WIDTH 800
#define HEIGHT 800


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

    free_cells(cell_board.cells, cell_board.size);

    return 0;
}

