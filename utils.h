#ifndef UTILS_H_
#define UTILS_H_

int parse_cmd_arg(int argc, char **argv);
double **allocateMatrix(int matrixSize);
double ****allocateData(int matrixSize, int nmats);
double ***allocate3DMatrix(int matrixSize, int nmats);
void printResult(int matrixSize, double **c);
void printCoarse(double ***coarse, int matrixSize, int nmats);
int mat_diff_acum(double **A, double **B, int matrixSize);
void free_memory(double **A, double **B, double **C, double **fine);
void free_data(double ****data, int matrixSize, int nmats);
void free_coarse(double ***coarse, int matrixSize, int nmats);
void storeData(FILE *fh, double ****data, int matrixSize, int nmats);
void getMatrices(double ****data, double **a, double **b, int matrixSize, int index);

#endif /* UTILS_H_ */
