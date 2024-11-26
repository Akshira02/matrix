#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/*
 * Main function to calculate the determinant of a matrix from a file.
 * Parameters:
 * - argc: Number of command-line arguments.
 * - argv: Array of command-line arguments.
 * Returns:
 * - 0 on success, non-zero on failure.
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <matrix_file>\n", argv[0]);
        return 1;
    }

    // Read the matrix from the file
    Matrix* matrix = read_matrix(argv[1]);

    // Calculate the determinant
    double determinant = calculate_determinant(matrix);

    // Print the determinant
    printf("The determinant is %.2f\n", determinant);

    // Free the matrix memory
    free_matrix(matrix);

    return 0;
}
