#include "snake_math.h"

Matrix3x3 identity_matrix()
{
    Matrix3x3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.data[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
    return result;
}

Matrix3x3 translate(float x, float y) {
    Matrix3x3 result = identity_matrix();
    result.data[0][2] = x;
    result.data[1][2] = y;
    return result;
}

Matrix3x3 scale(float x, float y) {
    Matrix3x3 result = identity_matrix();
    result.data[0][0] = x;
    result.data[1][1] = y;
    return result;
}

void print_matrix(const Matrix3x3 *m)
{
    for (int i = 0; i < 3; i++) {
        printf("[ %f %f %f ]\n", m->data[i][0],m->data[i][1],m->data[i][2]);
    }
}

Matrix3x3 multiply_matrices(const Matrix3x3 *a, const Matrix3x3 *b)
{
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result.data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    return result;
}
