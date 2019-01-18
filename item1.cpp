#include <iostream>
#include "time.h"
#include<omp.h>

using namespace std;

#define MATRIXLENGTH 10000
#define TIME 10

double matrix[MATRIXLENGTH][MATRIXLENGTH] = { 0.0 };

double newMatrix[MATRIXLENGTH][MATRIXLENGTH] = { 0.0 };

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
void calculate(double matrix[MATRIXLENGTH][MATRIXLENGTH], double newMatrix[MATRIXLENGTH][MATRIXLENGTH], int height, int length, int ompNum) {
	//    被除数，如果在四个角上，只能计算2邻域，则被除数应该为2，在边上，只能计算3个邻域，被除数应该是3
	int num = 0;
	omp_set_num_threads(ompNum);
#pragma omp parallel
	{
#pragma omp for private(num)
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < length; j++) {
				if (i > 0) {newMatrix[i][j] += matrix[i - 1][j]; num += 1;}
				if (j > 0) {newMatrix[i][j] += matrix[i][j - 1]; num += 1;}
				if (i < height - 1) {newMatrix[i][j] += matrix[i + 1][j]; num += 1;}
				if (j < length - 1) {newMatrix[i][j] += matrix[i][j + 1]; num += 1;}
				newMatrix[i][j] /= num;
				num = 0;
			}
		}
	}
};



int main() {
	double duration[TIME] = { 0.0 };
	for (int d = 0; d < TIME; d++) {
		double start = omp_get_wtime();
		calculate(matrix, newMatrix, MATRIXLENGTH, MATRIXLENGTH, 4);
		double end = omp_get_wtime();
		duration[d] = end - start;
		printf("%f s  ", duration[d]);
	}
	cout << "average time is : " << getAverage(duration) << endl;
	return 0;
}