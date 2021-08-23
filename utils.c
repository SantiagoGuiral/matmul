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

double ****allocateData(int matrixSize, int nmats){
	int i,j,k;
	double ****data;
	int pair=2;

	//Allocate structure for the file data
	data = (double ****) malloc(nmats*sizeof(double***));

	//POINTER 4D array to iterate the data file
	for (i=0;i<nmats;i++){
		data[i]=(double ***) malloc(pair*sizeof(double**));
		if (data[i]==NULL) return NULL;
		for(j=0;j<pair;j++){
			data[i][j]=(double **) malloc(matrixSize*sizeof(double*));
			if (data[i][j]==NULL) return NULL;
			for(k=0;k<matrixSize;k++){
					data[i][j][k]=(double*) malloc(matrixSize*sizeof(double));
					if (data[i][j][k]==NULL) return NULL;
			}
		}
	}
	return data;
}

double ***allocate3DMatrix(int matrixSize, int nmats){
	double ***coarse;
	int i,j;
	coarse = (double ***) malloc(nmats*sizeof(double**));
	for (i=0;i<nmats;i++){
		coarse[i]= (double **) malloc(matrixSize*sizeof(double*));
		if (coarse[i]==NULL) return NULL;
		for (j=0;j<matrixSize;j++){
			coarse[i][j]= (double*) malloc (matrixSize*sizeof(double));
			if (coarse[i][j]==NULL) return NULL;			
		}
	}
	return coarse;
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

void printCoarse(double ***coarse, int matrixSize, int nmats){
	int i,j,k;
	for (i=0;i<nmats;i++){
		for(j=0;j<matrixSize;j++){
			for (k=0;k<matrixSize;k++){
				printf("%lf ",coarse[i][j][k]);
			}
			printf ("\n");
		}
		printf("\n\n");
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

void free_memory(double **A, double **B, double **C, double **fine){
	free(*A);
	free(*B);
	free(*C);
	free(*fine);
	free(A);
	free(B);
	free(C);
	free(fine);
}

void free_data(double ****data, int matrixSize, int nmats){
	int i,j,k;
	int pair=2;
	
	for(i=0;i<nmats;i++){
		for(j=0;j<pair;j++){
        	for(k=0;k<matrixSize;k++){
           		free(data[i][j][k]);
        	}
        	free(data[i][j]);
    	}
    	free(data[i]);
	}
	free(data);
}

void free_coarse(double ***coarse, int matrixSize, int nmats){
	int i,j;
	for (i=0;i<nmats;i++){
		for (j=0;j<matrixSize;j++){
			free(coarse[i][j]);
		}
		free(coarse[i]);
	}
	free(coarse);
}

void storeData(FILE *fh, double ****data, int matrixSize, int nmats){
	int i,j,k;
	for(i=0;i<nmats;i++){
		for (j=0;j<matrixSize;j++){
			for(k=0;k<matrixSize;k++){
				fscanf(fh,"%lf",&data[i][0][j][k]);
			}
		}
		for (j=0;j<matrixSize;j++){
			for(k=0;k<matrixSize;k++){
				fscanf(fh,"%lf",&data[i][1][j][k]);
			}
		}
	}
}

void getMatrices(double ****data, double **a, double **b, int matrixSize, int index){
	int i,j;
	for (i=0;i<matrixSize;i++){
		for (j=0;j<matrixSize;j++){
			a[i][j]=data[index][0][i][j];
			b[i][j]=data[index][1][i][j];
		}
	}
}

