 /*
 ============================================================================
 Name        : matmul.c
 Author      : Santiago Rios - Emmanuel Gomez
 Version     :
 Copyright   : Your copyright notice
 Description : Matmul main file 
 ============================================================================
 */

//#include <valgrind/callgrind.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "sequential.h"
#include "finemm.h"
#include "coarsemm.h"

#define BILLION 1000000000L
#define CLOCKID CLOCK_REALTIME

int main(int argc, char **argv) {

	//CALLGRIND_START_INSTRUMENTATION;	

	//Time measures
	struct timespec start, stop;
	double tseq,  tfine;//, tcoarse;

	//Gets the number of threads
	int threads=parse_cmd_arg(argc,argv);

	//Pointers to the Matrices
	double **a, **b, **c, **fine, ***coarse;
	double ****data;
	int matrixSize;
	int nmats;

	//File
	char *fname = "matrices_test.dat"; //Change to matrices_large.dat for performance evaluation
	FILE *fh;

	fh = fopen(fname, "r");
	//First line indicates how many pairs of matrices there are and the matrix size
	fscanf(fh, "%d %d\n", &nmats, &matrixSize);
	
	//Allocates and stores the data from the file to the heap
	data=allocateData(matrixSize,nmats);
	storeData(fh,data,matrixSize,nmats);

	fclose(fh);

	printf("Start\n");

	//Allocate matrices memory
	a = allocateMatrix(matrixSize);
	b = allocateMatrix(matrixSize);
	c = allocateMatrix(matrixSize);
	fine = allocateMatrix(matrixSize);
	coarse = allocate3DMatrix(matrixSize,nmats);

	printf("Loading %d pairs of square matrices of size %d from %s...\n", nmats, matrixSize, fname);
		
	//Sequencial multiplication
	clock_gettime(CLOCKID, &start);
	matmulseq(data,a,b,c,matrixSize,nmats);
	clock_gettime(CLOCKID, &stop);
	tseq=( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;

	
	//Parallel fine multiplication
	clock_gettime(CLOCKID, &start);
	for (int i=0;i<nmats;i++){
		getMatrices(data,a,b,matrixSize,i);
		matmulfine(a,b,fine,threads,matrixSize);
		printResult(matrixSize,fine);
	}
	clock_gettime(CLOCKID, &stop);
	tfine=( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
	
	/*
	//Parallel coarse multiplication
	clock_gettime(CLOCKID, &start);
	matmulcoarse(a,b,coarse,data,threads,matrixSize,nmats);
	printCoarse(coarse,matrixSize,nmats);
	clock_gettime(CLOCKID, &stop);
	tcoarse=( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
	*/
	
	printf("tseq: %0.8f \t",tseq);
	printf("tfine:  %0.8f\n",tfine);
	//printf("tcoarse: %0.8f \t",tcoarse);

	printf("Done.\n");
	free_memory(a,b,c,fine);
	free_data(data,matrixSize,nmats);
	free_coarse(coarse,matrixSize,nmats);
	//CALLGRIND_STOP_INSTRUMENTATION;
	return 0;
}
