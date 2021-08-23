#ifndef FINEMM_H_
#define FINEMM_H_

#include <stdint.h>

#include "pt_queue.h"

//Thread data structure
typedef struct{
	uint8_t T;				//Thread number
	uint32_t matrixSize;	//Matrix Size
	uint32_t nlines;		//Lines
	uint16_t idx;			//Matrix Index
	double **A;				//Input
	double **B;				//Input
	double **fine;			//Ouput
	pt_queue_t msg_in;		//Main message to thread
	pt_queue_t* msg_out;	//Thread message work is done
}thread_data_fine;

void matmulfine(double **A, double **B, double **fine, uint8_t T, uint32_t matrixSize);

#endif /* FINEMMH_ */
