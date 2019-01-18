// openMP+Marrix.cpp: 定义控制台应用程序的入口点。
//

#include <iostream>
#include <windows.h>
#include<omp.h>

using namespace std;

//初始化二维数组
double **initMatrix(int column, int row);
//初始化全0二维数组（这个数组是用来存储吧）
double **initcopy_Matrix(int column, int row);
//计算四邻域均值
void average(double **matrix, double **matrix_copy, int column, int row);


int main()
{
    int column = 10000, row = 10000;

    //    需要计算均值的函数
    for (int i = 0; i < 10; i++) {


        double **matrix = initMatrix(column, row);
        double **matrix_copy = initcopy_Matrix(column, row);
        double start = omp_get_wtime();

        average(matrix, matrix_copy, column, row);

        double end = omp_get_wtime();
        cout << "openmp:" << endl;
        cout << "total_time: " << (end - start) << "s" << endl;
    }
//    system("pause");
    return 0;
}

double **initMatrix(int column, int row) {
    double ** matrix;
    matrix = new double *[column];

    for (int i = 0; i < column; i++) {
        matrix[i] = new double[row];
        for (int j = 0; j < row; j++) {
            matrix[i][j] = rand() % 100;
        }
    }

    return matrix;
}

double **initcopy_Matrix(int column, int row) {
    double ** matrix;
    matrix = new double *[column];
    for (int i = 0; i < column; i++) {
        matrix[i] = new double[row];
        for (int j = 0; j < row; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void average(double **matrix, double **matrix_copy, int column, int row) {
    omp_set_num_threads(4);
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < column; i++) {
            for (int j = 0; j < row; j++) {
                if (i > 0) {
                    matrix_copy[i][j] += matrix[i - 1][j];
                }
                if (j > 0) {
                    matrix_copy[i][j] += matrix[i][j - 1];
                }
                if (i < column - 1) {
                    matrix_copy[i][j] += matrix[i + 1][j];
                }
                if (j < row - 1) {
                    matrix_copy[i][j] += matrix[i][j + 1];
                }
                matrix_copy[i][j] /= 4;

            }
        }
    }
    delete matrix_copy;
};