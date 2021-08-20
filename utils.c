#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

int parse_cmd_arg(int argc, char**argv){
	int threads=1;
	for (int i=1; i<argc; i++){
		if (strcmp(argv[i],"-T")==0){
			if (i<argc-1){
				threads=atoi(argv[++i]);
			}
		}
		else{
			printf("Invalid argument: %s\n",argv[i]);
		}
	}
	return threads;
}

double **allocateMatrix(int matrixSize) {
	//printf("The matrix size is: %d\n",matrixSize);
	int i;
	double *vals, **temp;

	// allocate space for values of a matrix
	vals = (double *) malloc (matrixSize * matrixSize * sizeof(double));

	// allocate vector of pointers to create the 2D array
	temp = (double **) malloc (matrixSize * sizeof(double*));

	for(i=0; i < matrixSize; i++)
		temp[i] = &(vals[i * matrixSize]);

	return temp;
}

double ***allocateStructMatrix(int matrixSize, int T){

	int i,j;
	double ***structure;
	
	//Allocate structure for the matrices
	structure = (double ***) malloc(T*sizeof(double**));
	
	//Pointers 3D array
	for(i=0;i<T;i++){
		structure[i] = (double **) malloc(matrixSize*sizeof(double*));
		for(j=0;j<matrixSize;j++){
			structure[i][j] = (double*) malloc(matrixSize*sizeof(double));
		}
	}

	return structure;
}

void printResult(int matrixSize, double **c){
	int i, j;
	for(i=0;i<matrixSize;i++){
		for(j=0;j<matrixSize;j++){
			printf("%lf ", c[i][j]);
		}
		printf("\n");
	}
}

int mat_diff_acum(double **A, double **B, int matrixSize){
	int ACC=0;
	for (int i=0;i<matrixSize;i++){
		for (int j=0;j<matrixSize;j++){
			if(A[i][j] != B[i][j]){
				ACC+=1;
			}
		}
	}
	return ACC;
}

void free_memory(double **A, double **B, double **C, double ***coarse, double **fine){
	free(*A);
	free(*B);
	free(*C);
	free(**coarse);
	free(*coarse);
	free(*fine);
	free(A);
	free(B);
	free(C);
	free(coarse);
	free(fine);
}

void readFile (double **A, double **B, FILE *fh, int matrixSize){
	int i,j;
	for (i=0;i<matrixSize;i++){
		for(j=0;j<matrixSize;j++){
			fscanf(fh,"%lf",&A[i][j]);
		}
	}
	for (i=0;i<matrixSize;i++){
		for(j=0;j<matrixSize;j++){
			fscanf(fh,"%lf",&B[i][j]);
		}
	}

}
