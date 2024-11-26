#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/*
 * Function to read a matrix from a file.
 * Parameters:
 * - file_path: Path to the file containing the matrix.
 * Returns:
 * - A pointer to the dynamically allocated Matrix structure.
 */
Matrix* read_matrix(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    int size;
    fscanf(file, "%d", &size); // Read the dimension (NxN matrix)

    // Allocate memory for the Matrix structure
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix->size = size;

    // Allocate memory for the 2D array
    matrix->data = malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        matrix->data[i] = malloc(size * sizeof(double));
        for (int j = 0; j < size; j++) {
            fscanf(file, "%lf", &matrix->data[i][j]); // Read the actual matrix data
        }
    }

    fclose(file);
    return matrix;
}

/*
 * Function to free the memory of a Matrix structure.
 * Parameters:
 * - matrix: Pointer to the Matrix structure.
 */
void free_matrix(Matrix* matrix) {
    for (int i = 0; i < matrix->size; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

/*
 * Recursive function to calculate the determinant of a matrix.
 * Parameters:
 * - size: The size of the current matrix (NxN).
 * - matrix: The 2D array representing the matrix.
 * Returns:
 * - The determinant as a double.
 */
double calculate_determinant_recursive(int size, double** matrix) {
    if (size == 1) {
        return matrix[0][0]; // Base case for a 1x1 matrix
    }

    if (size == 2) {
        // Base case for a 2x2 matrix
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }

    double determinant = 0.0;

    // Allocate memory for the submatrix (N-1 x N-1)
    double** submatrix = malloc((size - 1) * sizeof(double*));
    for (int i = 0; i < size - 1; i++) {
        submatrix[i] = malloc((size - 1) * sizeof(double));
    }

    // Expand along the first row
    for (int col = 0; col < size; col++) {
        // Create the submatrix by skipping row 0 and column col
        for (int i = 1; i < size; i++) {
            int sub_col = 0;
            for (int j = 0; j < size; j++) {
                if (j == col) continue; // Skip the current column
                submatrix[i - 1][sub_col] = matrix[i][j];
                sub_col++;
            }
        }

        // Calculate the cofactor and determinant of the submatrix
        double cofactor = (col % 2 == 0 ? 1 : -1) * matrix[0][col];
        determinant += cofactor * calculate_determinant_recursive(size - 1, submatrix);
    }

    // Free the memory allocated for the submatrix
    for (int i = 0; i < size - 1; i++) {
        free(submatrix[i]);
    }
    free(submatrix);

    return determinant;
}

/*
 * Wrapper function to calculate determinant using the Matrix struct.
 * Parameters:
 * - matrix: Pointer to the Matrix structure.
 * Returns:
 * - The determinant of the matrix.
 */
double calculate_determinant(Matrix* matrix) {
    return calculate_determinant_recursive(matrix->size, matrix->data);
}
