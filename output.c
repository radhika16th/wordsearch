/*
 * Prints the solved puzzle in purple.
 *
 * Raadhikka Gupta
 * SFWRENG 2XC3
 * Nov 27, 2025
 */

#include "output.h"
#include <stdio.h>

/*
 * Prints the puzzle board.
 */
void printSolved(char **board, int rows, int cols, int *mark) 
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            char ch = board[r][c];

            // If this character is part of a found word, print in color
            if (mark[r * cols + c] == 1) {
                fprintf(stdout, "\033[1;35m%c\033[0m", ch);
            } 
            
            // Print without the color
            else {
                fprintf(stdout, "%c", ch);
            }
        }

        fprintf(stdout, "\n");
    }
}