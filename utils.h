#ifndef UTILS_H_
#define UTILS_H_

int parse_cmd_arg(int argc, char **argv);
double **allocateMatrix(int matrixSize);
double ***allocateStructMatrix(int matrixSize,int T);
void printResult(int matrixSize, double **c);
int mat_diff_acum(double **A, double **B, int matrixSize);
void free_memory(double **A, double **B, double **C, double ***coarse, double **fine);
void readFile(double **A, double **B, FILE *fh, int matrixSize);

#endif /* UTILS_H_ */
