 /*
 ============================================================================
 Name        : matmul.c
 Author      : Santiago Rios - Emmanuel Gomez
 Version     :
 Copyright   : Your copyright notice
 Description : Matmul main file 
 ============================================================================
 */

#include <valgrind/callgrind.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "sequential.h"
//#include "finemm.h"
//#include "coarsemm.h"

#define BILLION 1000000000L
#define CLOCKID CLOCK_REALTIME

int main(int argc, char **argv) {

	CALLGRIND_START_INSTRUMENTATION;	

	//Time measures
	struct timespec start, stop;
	double tseq, tcoarse, tfine;

	//Gets the number of threads
	int threads=parse_cmd_arg(argc,argv);

	//Pointers to the Matrices
	double **a, **b, **c;
	double ****data;
	int matrixSize;
	int nmats;

	//Automates output results 
	char *datname="time.dat";
	FILE *fdat;

	//File
	char *fname = "matrices_test.dat"; //Change to matrices_large.dat for performance evaluation
	FILE *fh;

	fh = fopen(fname, "r");
	//First line indicates how many pairs of matrices there are and the matrix size
	fscanf(fh, "%d %d\n", &nmats, &matrixSize);
	
	//Allocates and stores the data from the file to the heap
	data=allocateData(matrixSize,nmats);
	if (data==NULL) return 0;
	storeData(fh,data,matrixSize,nmats);

	fclose(fh);

	printf("Start\n");

	//Allocate matrices memory
	a = allocateMatrix(matrixSize);
	b = allocateMatrix(matrixSize);
	c = allocateMatrix(matrixSize);

	printf("Loading %d pairs of square matrices of size %d from %s...\n", nmats, matrixSize, fname);
		
	//Sequencial multiplication
	clock_gettime(CLOCKID, &start);
	matmulseq(data,a,b,c,matrixSize,nmats);
	clock_gettime(CLOCKID, &stop);
	tseq=( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
	
	/*
	//Parallel coarse multiplication
	clock_gettime(CLOCKID, &start);
	printf("Not working yet coarse\n");
	clock_gettime(CLOCKID, &stop);
	tcoarse=( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;

	//Parallel fine multiplication
	clock_gettime(CLOCKID, &start);
	printf("Suposs fine");
	for (int i=0;i<nmats;i++){
		getMatrices(data,a,b,matrixSize,i);
		finematmul(a,b,fine,threads,matrixSize);
		printResult(matrixSize,fine);
	}
	clock_gettime(CLOCKID, &stop);
	tfine=( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
	*/	

	printf("tseq: %0.8f \t",tseq);
	//printf("tcoarse: %0.8f \t",tcoarse);
	//printf("tfine:  %0.8f\n",tfine);

	//Stores results in data file
	fdat =fopen(datname,"a");
	fprintf(fdat,"%0.8f\n",tseq);
	fclose(fdat);

	printf("Done.\n");
	free_memory(a,b,c);
	free_data(data,matrixSize,nmats);
	CALLGRIND_STOP_INSTRUMENTATION;
	return 0;
}
