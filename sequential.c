#include <stdio.h>

#include "sequential.h"
#include "utils.h"

void mm(int matrixSize, double** a, double** b, double** c) {
	int i,j,k;
	double sum;
	// matrix multiplication
	for (i = 0; i < matrixSize; i++) {
		for (j = 0; j < matrixSize; j++) {
			sum = 0.0;
			// dot product
			for (k = 0; k < matrixSize; k++) {
				sum = sum + a[i][k] * b[k][j];
			}
			c[i][j] = sum;
		}
	}
}

void serial(FILE* fh, int nmats, int matrixSize, double** a, double** b, double** c){
	int i,j,k;
	for(k=0;k<nmats;k++){
		for(i=0;i<matrixSize;i++){
			for(j=0;j<matrixSize;j++){
				fscanf(fh, "%lf", &a[i][j]);
			}
		}
		for(i=0;i<matrixSize;i++){
			for(j=0;j<matrixSize;j++){
				fscanf(fh, "%lf", &b[i][j]);
			}
		}

		printf("Sequential... Multiplying two matrices...\n"); //Remove this line for performance tests
		mm(matrixSize,a,b,c);
		printResult(matrixSize, c); //Remove this line for performance tests
	}

}
