#ifndef UTILS_H_
#define UTILS_H_


int parse_cmd_arg(int argc, char **argv);
double **allocateMatrix(int matrixSize);
double ****allocateData(int matrixSize, int nmats);
void printResult(int matrixSize, double **c);
int mat_diff_acum(double **A, double **B, int matrixSize);
void free_memory(double **A, double **B, double **C);
void free_data(double ****data, int matrixSize, int nmats);
void storeData(FILE *fh, double ****data, int matrixSize, int nmats);
void getMatrices(double ****data, double **a, double **b, int matrixSize, int index);

#endif /* UTILS_H_ */
