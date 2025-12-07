# To help with compiling the code easily.
# Raadhikka Gupta
# SFWRENG 2XC3
# Nov 27, 2025

# Compile normal version
wordsearch: wordsearch.c read.c copy.c find.c output.c errors.c read.h copy.h find.h output.h errors.h
	gcc wordsearch.c read.c copy.c find.c output.c errors.c -o wordsearch