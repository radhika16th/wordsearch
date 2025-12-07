/*
 * Helper function for safe memory allocation.
 *
 * Raadhikka Gupta
 * SFWRENG 2XC3
 * Nov 27, 2025
 */

#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Assigns a block of memory and checks if malloc succeeded.
 */
void *allocMemory(size_t size) {
    void *p = malloc(size);

    // Check if allocation failed
    if (!p) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return p;
}