/*
 * Creates a new 2D board and copies all characters from the old board.
 *
 * Raadhikka Gupta
 * SFWRENG 2XC3
 * Nov 27, 2025
 */

#include "copy.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Copies the board
 */
char **copyBoard(char **board, int rows, int cols) {
    // Allocate the row pointer array.
    char **newBoard = allocMemory(rows * sizeof(char*));

    // Copy each row
    for (int r = 0; r < rows; r++) {
        newBoard[r] = allocMemory(cols * sizeof(char));

        // Copy each character
        for (int c = 0; c < cols; c++) {
            newBoard[r][c] = board[r][c];
        }
    }

    return newBoard;
}