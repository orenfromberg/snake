#include <stdio.h>
#include <assert.h>
#include "snake.h"

void main(int argc, char * argv) {
    Matrix3x3 m = scale(10,14);
    Matrix3x3 n = translate(3,2);
    Matrix3x3 result = multiply_matrices(&m, &n);
    print_matrix(&result);
    return 0;
}
