#include <stdio.h>

void daxpy_c(int n, double A, double* vectorX, double* vectorY, double* vectorZ) {
    for (int i = 0; i < n; i++) {
        vectorZ[i] = A * vectorX[i] +vectorY[i];
    }
}