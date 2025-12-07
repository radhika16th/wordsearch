/*
 * Main program for the word search puzzle solver.
 *
 * Raadhikka Gupta
 * SFWRENG 2XC3
 * Nov 27, 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "copy.h"
#include "find.h"
#include "output.h"
#include "errors.h"

/*
 * Prints information about the program
 */
void help() {
    printf("wordsearch - Word Search Puzzle Solver\n");
    printf("Reads a puzzle grid and a list of words, then colours the found words.\n");
    printf("\n");
    printf("Usage:\n");
    printf("  wordsearch [FILE]\n");
    printf("\n");
    printf("If file is not provided, the puzzle is read from standard input. After that, enter a \"=\".\n");
    printf("Words to search for are always read from standard input.\n");
    printf("Hit Ctrl-D for the final solved puzzle.\n");
}

/*
 * The main program.
 */
int main(int argc, char *argv[]) {
    FILE *file;

    // Handle --help flag 
    if (argc >= 2 && strcmp(argv[1], "--help") == 0) {
        help();      // print help to stdout
        return 0;    // stop program
    }

    // Read puzzle from stdin
    if (argc == 1) {
        file = stdin;
    }

    // Read puzzle from file
    else if (argc == 2) {
        file = fopen(argv[1], "r");

        // If file could not be opened
        if (!file) {
            fprintf(stderr, "Could not open file.\n");
            exit(EXIT_FAILURE);
        }
    }

    else {
        fprintf(stderr, "Usage: wordsearch [FILE]\n");
        exit(EXIT_FAILURE);
    }

    int rows, cols;

    // Read the puzzle board from the file.
    char **board = readBoard(file, &rows, &cols);

    // Close the file
    if (file != stdin) {
        fclose(file);
    }

    // Each character in the puzzle has a match position
    int total = rows * cols;
    int *mark = allocMemory(total * sizeof(int));

    // Initialize all marks to zero
    for (int i = 0; i < total; i++) {
        mark[i] = 0;
    }
    
    // Read each word from standard input.
    char word[1024];
    while (scanf("%s", word) == 1) {
        findWord(board, rows, cols, word, mark);
    }

    // Print solved puzzle
    printSolved(board, rows, cols, mark);

    // Free memory
    for (int r = 0; r < rows; r++) {
        free(board[r]);
    }
    free(board);
    free(mark);

    return 0;
}
