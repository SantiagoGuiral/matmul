#ifndef MATMULSEQ_H_
#define MATMULSEQ_H_

void mm(int matrixSize, double** a, double** b, double**c);
void serial(FILE* fh, int nmats, int matrixSize, double** a, double** b, double** c);

#endif /* MATMULSEQ_H_ */
