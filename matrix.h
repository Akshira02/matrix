#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int size;
    double** data;
} Matrix;

Matrix* read_matrix(const char* file_path);
void free_matrix(Matrix* matrix);
Matrix* create_minor(Matrix* matrix, int excluded_row, int excluded_col);
double calculate_determinant(Matrix* matrix);

#endif // MATRIX_H
