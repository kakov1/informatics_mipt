#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Matrix{
      int size;
      double** data;
} Matrix;

int number_of_calls = 0;

int read_mat(Matrix* mat) {
    printf("Введите размер матрицы(одно натуральное число, не более 100): ");
    scanf("%d", &mat->size);
    printf("Введите матрицу построчно. Числа в строке разделены пробелами:\n");

    mat->data = (double**)calloc(mat->size, sizeof(double*));

    double num = 0;
    for (int i = 0; i < mat->size; i++) {
        mat->data[i] = (double*)calloc(mat->size, sizeof(double));

        for (int j = 0; j < mat->size; j++) {
            scanf("%lf", &num);
            mat->data[i][j] = num;
        }
    }

    printf("Теперь введите степень, в которую нужно возвести матрицу:\n");
    int power = 0;
    scanf("%i", &power);

    return power;
}

void copy_mat(Matrix* mat, Matrix* mat_copy) {
    mat_copy->size = mat->size;
    mat_copy->data = (double**)calloc(mat->size, sizeof(double*));

    for (int i = 0; i < mat->size; i++) {
        mat_copy->data[i] = (double*)calloc(mat->size, sizeof(double));

        for (int j = 0; j < mat->size; j++) {
            mat_copy->data[i][j] = mat->data[i][j];
        }
    }
}

void print(Matrix* mat) {
    for (int i = 0; i < mat->size; i++) {
        for (int j = 0; j < mat->size; j++) {
            printf("%f ", mat->data[i][j]);
        }
        printf("\n");
    }
}

void rowcol(Matrix* mat_old, Matrix* mat_new, Matrix* mat_new_copy, int row, int col) {
    double num = 0;
    for (int i = 0; i < mat_old->size; i++) {
        num += mat_old->data[row][i] * mat_new_copy->data[i][col];
    }
    mat_new->data[row][col] = num;
}

void mul(Matrix* mat_old, Matrix* mat_new) {
    Matrix mat_new_copy;
    copy_mat(mat_new, &mat_new_copy);
    
    if (mat_old == mat_new) {
        mat_old = &mat_new_copy;
    }

	for (int i = 0; i < mat_old->size; i++) {
        for (int j = 0; j < mat_old->size; j++) {
            rowcol(mat_old, mat_new, &mat_new_copy, i, j);
        }
    }
}

void pow_mat(Matrix* mat_old, Matrix* mat_new, int power) {
    number_of_calls++;
    if (power <= 1) {
        return;
    }
    else{
        if (power % 2 == 0) {
            pow_mat(mat_old, mat_new, power / 2);
            mul(mat_new, mat_new);
        }
        else {
            pow_mat(mat_old, mat_new, (power - 1) / 2);
            mul(mat_new, mat_new);
            mul(mat_old, mat_new);
        }
    }
}

int main() {
	Matrix mat_old;
    Matrix mat_new;

    int n = read_mat(&mat_old);
    copy_mat(&mat_old, &mat_new);
    pow_mat(&mat_old, &mat_new, n);
    
    print(&mat_new);
    printf("Number of calls: %i\n", number_of_calls);
}