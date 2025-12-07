/*
 * Reads the puzzle board from a file.
 *
 * Raadhikka Gupta
 * SFWRENG 2XC3
 * Nov 27, 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "errors.h"

/* 
 * Reads the puzzle from a file.
 */
char **readBoard(FILE *file, int *rows, int *cols) {
    // Read number of columns from the first token
    if (fscanf(file, "%d", cols) != 1 || *cols <= 0) {
        fprintf(stderr, "Invalid column count.\n");
        exit(EXIT_FAILURE);
    }

    *rows = 0;
    int capacity = 10;

    // Allocate pointer array for the board
    char **board = allocMemory(capacity * sizeof(char*));
    
    char token[1024];
    int colIndex = 0;

    // Allocate a new row (cols + 1 so we can add '\0')
    char *currentRow = allocMemory((*cols + 1) * sizeof(char));  // FIX

    // Read tokens until "="
    while (fscanf(file, "%s", token) == 1) {
        for (int i = 0; token[i] != '\0'; i++) {
            // "=" is the end
            if (token[i] == '=') {
                // If couldn't find the end
                if (colIndex != 0) {
                    fprintf(stderr, "Puzzle row incomplete before '='.\n");
                    exit(EXIT_FAILURE);
                }

                free(currentRow);
                return board;
            }

            currentRow[colIndex++] = token[i];

            // Row is full
            if (colIndex == *cols) {
                currentRow[colIndex] = '\0';

                // If already at capacity, expand it
                if (*rows == capacity) {
                    capacity *= 2;

                    // Resize the board array to hold more row pointers
                    board = realloc(board, capacity * sizeof(char*));

                    // Check if realloc failed
                    if (!board) {
                        fprintf(stderr, "Memory error.\n");
                        exit(EXIT_FAILURE);
                    }
                }
                
                // Add the current row
                board[*rows] = currentRow;
                (*rows)++;

                // Add memory for new row.
                currentRow = allocMemory((*cols + 1) * sizeof(char)); // FIX
                colIndex = 0;
            }
        }
    }

    // If = wasn't found, puzzle is not complete
    fprintf(stderr, "EOF before '='.\n");
    exit(EXIT_FAILURE);
}
