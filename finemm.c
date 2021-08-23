#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "finemm.h"
#include "pt_queue.h"
#include "utils.h"


void* thread_fine_mul(void* args){
	int i,j,k;
	double sum;

	//Perform casting of void* argument to real argument type
	thread_data_fine *dat = (thread_data_fine *)args;

	//Define data sector that will process the thread
	pt_queue_push(dat->msg_out, (void *)&dat->idx);

	uint16_t idx;
	//Iterates to assing work to the threads unitl no more available
	for (;;){
		pt_queue_pull(&dat->msg_in, (void *)&idx);

		uint32_t start = dat->nlines*idx;
		uint32_t end = 0;
		if (idx == (dat->matrixSize-1)){
			end = dat->matrixSize;
		}
		else{
			end = dat->nlines*(idx+1);
		}

		//Thread work
		printf("Fine... Multiplying two matrices...\n");
			for (i=start;i<end;i++){
				for(j=0;j<dat->matrixSize;j++){
					sum=0.0;
					//dot product
					for(k=0;k<dat->matrixSize;k++){
						sum = sum + dat->A[i][k]*dat->B[k][j];
					}
					dat->fine[i][j]=sum;
				}
			}
		pt_queue_push(dat->msg_out, (void *)&dat->idx);
	}
	return NULL;
}

void matmulfine(double **A, double **B, double **fine, uint8_t T, uint32_t matrixSize){

	//Allocate the threads data structures
	thread_data_fine* th_data = malloc(sizeof(thread_data_fine)*T);
	pthread_t* th_ids=malloc(sizeof(pthread_t)*T);
	
	//Avoids stacking the Cache
	uint32_t max_lines = ((uint32_t)(1<<16)/sizeof(double))/matrixSize;
	if (max_lines<1) max_lines=1;

	//nlines is the number of matmul each thread performs
	uint32_t nlines=matrixSize/T;
	if (nlines>max_lines) nlines=max_lines;

	//Set queue for threads to message main when work is done
	pt_queue_t msg_out;
	pt_queue_init(&msg_out,100,sizeof(uint16_t));

	//Limits the number of threads
	if (matrixSize<T){
		T=matrixSize;
		printf("Working with %d threads equals to the matrix size\n",T);
	}

	//Create threads
	for (int i=0;i<T;i++){
		th_data[i].idx = i;
		th_data[i].nlines = nlines;
		th_data[i].A = A;
		th_data[i].B = B ;
		th_data[i].fine = fine;
		th_data[i].T = T;
		th_data[i].matrixSize = matrixSize;
		pt_queue_init(&th_data[i].msg_in,20,sizeof(uint16_t));
		th_data[i].msg_out = &msg_out;
		pthread_create(&th_ids[i],NULL,thread_fine_mul,&th_data[i]);
	}
	
	//Controls the number of blocks to work - sends work to thread
	for (int i=0;i<matrixSize/nlines;i++){
		uint16_t th_idx =0;
		pt_queue_pull(&msg_out,(void*)&th_idx);//read thread index
		if(th_idx>T){
			printf("Problem found, program will be terminated");
			break;
		}
		pt_queue_push(&th_data[th_idx].msg_in,(void *)&i);//main sends idx to work assigned to the thread
	}

	//Cancels the threads when there is no work available
	for (int i=0;i<T;i++){
		uint16_t th_idx=0;
		pt_queue_pull(&msg_out,(void*)&th_idx);
		pthread_cancel(th_ids[th_idx]);
	}
}
