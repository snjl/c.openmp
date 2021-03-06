#include <iostream>
#include "time.h"
#include<omp.h>

using namespace std;
//初始化二维数组
#define MATRIXLENGTH 1002
#define TIME 100

double matrix[MATRIXLENGTH*MATRIXLENGTH] = { 0.0 };

double newMatrix[MATRIXLENGTH*MATRIXLENGTH] = { 0.0 };

void printMatrix(double **matrix, int height, int length) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
double getAverage(const double duration[TIME]) {
    double average = 0.0;
    for (int i = 0; i < TIME; i++) {
        average += duration[i];
    }
    return average / TIME;
}
void calculate(double matrix[MATRIXLENGTH*MATRIXLENGTH], double newMatrix[MATRIXLENGTH*MATRIXLENGTH], int ompNum) {
    omp_set_num_threads(ompNum);
#pragma omp parallel
    {
#pragma omp for
        for (int i = MATRIXLENGTH; i < MATRIXLENGTH*(MATRIXLENGTH - 1); i++) {
            newMatrix[i] = (matrix[i - MATRIXLENGTH] + matrix[i + MATRIXLENGTH] + matrix[i - 1] + matrix[i + 1]) / 4;
        }
    }
};


int main() {
    double duration[TIME] = { 0.0 };
    for (int d = 0; d < TIME; d++) {
        double start = omp_get_wtime();
        calculate(matrix, newMatrix, 4);
        double end = omp_get_wtime();
        duration[d] = end - start;
        printf("%f s  ", duration[d]);
    }
    cout << "average time is : " << getAverage(duration) << endl;
    return 0;
}
