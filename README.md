# matmul

Matmul is a C program developed for the Computer's Architecture curse in the University of Antioquia.
The code implements two multithreading algorithms that multyply matrices stored in a .dat file.

The program was developed in a Ubuntu OS and is executed from the terminal.

## Features

- Multithreading exeuction with performance measurements
- Coarse multithreading
- Fine multithreading

## Create executeable file

Run the make file to compile the program corresponding files.

```
make
```

## Execute the code

matmul requires a .dat file that has the matrices to multiply and also requires th especifiy the number of threads used.

#### Single execution

Example of execution with 4 threads

```
./matmul -T 4
```

#### Multiple executions

To execute matmult and compare different performance results, the user can use the automate bash file. The user especifies the number of threads used and also can generate a time.dat file with time metrics.

```
chmod 777 automate.sh 
./automate.sh 
```
