#ifndef SNAKE_MATH_H
#define SNAKE_MATH_H

#include <stdio.h>

typedef struct {
    float data[3][3];
} Matrix3x3;

Matrix3x3 identity_matrix();
Matrix3x3 translate(float x, float y);
void translate_mat(Matrix3x3 * m, float x, float y);
Matrix3x3 scale(float x, float y);
void scale_mat(Matrix3x3 * m, float a, float b);
void print_matrix(const Matrix3x3 * m);

Matrix3x3 multiply_matrices(const Matrix3x3 * a, const Matrix3x3 * b);

#endif