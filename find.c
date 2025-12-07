/*
 * Searches for words in the puzzle board.
 *
 * Raadhikka Gupta
 * SFWRENG 2XC3
 * Nov 27, 2025
 */

#include "find.h"
#include <string.h>
#include <stdio.h>

/*
 * Checks if a given position is inside the board.
 */
static int isInBounds(int row, int col, int totalRows, int totalCols) {
    return (row >= 0 && row < totalRows && col >= 0 && col < totalCols);
}

/*
 * Tries to find the word on the board in all directions.
 */
static int searchWord(char **board, int rows, int cols, const char *word, int *mark)
{
    int len = strlen(word);

    // Directions
    int directionRow[8] = { 0,  0,  1, -1,  1,  1, -1, -1 };
    int directionCol[8] = { 1, -1,  0,  0,  1, -1,  1, -1 };

    // Try every cell as a starting point
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            // Match the first letter
            if (board[r][c] != word[0])
                continue;

            // Try all 8 directions
            for (int d = 0; d < 8; d++) {
                int checkRow = r;
                int checkCol = c;
                int characterIndex;

                // Check other characters
                for (characterIndex = 1; characterIndex < len; characterIndex++) {
                    checkRow += directionRow[d];
                    checkCol += directionCol[d];

                    // Stop if out of bounds
                    if (!isInBounds(checkRow, checkCol, rows, cols))
                        break;

                    // Stop if not match
                    if (board[checkRow][checkCol] != word[characterIndex])
                        break;
                }

                // If it matches completely
                if (characterIndex == len) {
                    // Mark all the letters of the word
                    checkRow = r;
                    checkCol = c;

                    // Found the word
                    for (int m = 0; m < len; m++) {
                        mark[checkRow * cols + checkCol] = 1;
                        checkRow += directionRow[d];
                        checkCol += directionCol[d];
                    }
                    return 1;
                }
            }
        }
    }

    return 0;
}

/*
 * Makes a reversed copy of the word.
 */
static void reverse(char *reversed, const char *original)
{
    int len = strlen(original);

    // Copy characters from end of src to start of dest
    for (int i = 0; i < len; i++)
        reversed[i] = original[len - 1 - i];

    // Add the null terminator
    reversed[len] = '\0';
}

/*
 * Tries to find the word forwards and backwards, on the board.
 */
int findWord(char **board, int rows, int cols, const char *word, int *mark)
{
    char rev[256];
    reverse(rev, word); // reverses the word

    // Try forward
    if (searchWord(board, rows, cols, word, mark))
        return 1;

    // Try backward
    if (searchWord(board, rows, cols, rev, mark))
        return 1;

    return 0;
}
