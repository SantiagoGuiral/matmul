 /*
 ============================================================================
 Name        : matmul.c
 Author      : Santiago Rios - Emmanuel Gomez
 Version     :
 Copyright   : Your copyright notice
 Description : 
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "sequential.h"
//#include "coarsemul.h"
//#include "finemul.h"

#define BILLION 1000000000L
#define CLOCKID CLOCK_REALTIME

int main(int argc, char **argv) {

	//Time measures
	struct timespec start, stop;
	double tseq, tcoarse, tfine;

	//Gets the number of threads
	int threads=parse_cmd_arg(argc,argv);
	//printf("The number of threads is: %d\n",threads);

	//Pointers to the Matrices
	double **a, **b, **c, ***coarse, **fine;
	int matrixSize;
	int nmats;

	//File
	char *fname = "matrices_test.dat"; //Change to matrices_large.dat for performance evaluation
	FILE *fh;

	char *datname="time.dat";
	FILE *fdat;

	fh = fopen(fname, "r");
	//First line indicates how many pairs of matrices there are and the matrix size
	fscanf(fh, "%d %d\n", &nmats, &matrixSize);
	fclose(fh);


	printf("Start\n");

	//Allocate matrices memory
	a = allocateMatrix(matrixSize);
	b = allocateMatrix(matrixSize);
	c = allocateMatrix(matrixSize);
	coarse = allocateStructMatrix(matrixSize,threads);
	fine = allocateMatrix(matrixSize);

	printf("Loading %d pairs of square matrices of size %d from %s...\n", nmats, matrixSize, fname);
	
	//Multiplication: sequential and parallel
	for (int i=0;i<2;i++){
		
		//Multiplication: serial and parallel
		switch(i){
			case 0:
				//Serial multiplication
				clock_gettime(CLOCKID, &start);
				serial(fh,nmats,matrixSize,a,b,c);
				clock_gettime(CLOCKID, &stop);
				tseq=( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
				break;
			case 1:
				//Parallel coarse multiplication
				clock_gettime(CLOCKID, &start);
				//coarsematmul(a,b,coarse,threads,matrixSize,nmats,fh);
				clock_gettime(CLOCKID, &stop);
				tcoarse=( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
				break;
			case 2:
				//Parallel fine multiplication
				clock_gettime(CLOCKID, &start);
				//finematmul(a,b,fine,threads,matrixSize);
				clock_gettime(CLOCKID, &stop);
				tfine=( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
				break;
			default:
				printf("Error\n");
				break;
		}	
	}


	printf("Sequential execution time:\t %0.8f\n",tseq);
	printf("Parallel coarse execution time:\t %0.8f\n",tcoarse);
	printf("Parallel fine exeuction time: \t %0.8f\n",tfine);

	//Stores results in data file
	fdat =fopen(datname,"a");
	fprintf(fdat,"%0.8f,%0.8f,%0.8f\n",tseq,tcoarse,tfine);
	fclose(fdat);

	// Free memory
	free_memory(a,b,c,coarse,fine);

	printf("Done.\n");
	return 0;
}
