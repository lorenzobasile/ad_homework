# Algorithmic Design homework 1: Strassen's Algorithm
This repository contains my implementation of Strassen's algorithm for matrix multiplication, with some modifications to generalize it to deal with rectangular matrices. The final aim of this homework is to compare the time performances of Strassen algorithm against naive matrix multiplication algorithm when operating on rectangular matrices.

The implementation of the naive algorithm is contained in the file `matrix.c`, while `strassen.c` contains the implementation of Strassen algorithm (in two different versions, one with optimized memory usage and one without these optimizations). These algorithms are compared in `main.c` by running them on randomly initialized matrices of increasing sizes. To obtain the executable `strassen_test`, it is sufficient to compile using the command `make`.





This repository contains some code to simplify the implementation and the testing of the Strassen's algorithm for matrix multiplication.

In order to test the differences in term of execution-time between the naive algorithm and the Strassen's algorithm, you need to implement both the algorithms. The former must be implementated by the function `naive_matrix_multiplication` in the file [matrix.c](matrix.c) and the latter by the function `strassen_matrix_multiplication` in the file [strassen.c](strassen.c).

A Makefile can be produced by using [cmake](https://cmake.org/) as follows:
```bash
cmake -G "Unix Makefiles" CMakeLists.txt
```
Afterwards you can compile the code by executing `make`. This produces an executable named `strassen_test` which can be executed in POSIX systems by using the command:
```bash
./strassen_test 
n Naive Alg.  Strassen's Alg. Same result
1	0.000000	0.000000	1
2	0.000000	0.000000	1
4	0.000000	0.000000	1
8	0.000000	0.000000	1
16	0.000000	0.000000	1
32	0.000000	0.000000	1
64	0.000000	0.000000	1
128	0.000000	0.000000	1
256	0.000000	0.000000	1
512	0.000000	0.000000	1
1024	0.000000	0.000000	1
2048	0.000000	0.000000	1
4096	0.000000	0.000000	1
```

The first column in the output report the number of the rows and columns in the tested matrixes. 

The second and third columns in the output reports the execution-time in seconds of the implementations of the naive algorithm and of the Strassen's algorithm, respectively. Since the two algorithms are not implemented in the repository, `strassen_test` initially reports 0 seconds for both of them. 

Finally, the last column, which is excusively meant to validate the implementations, contains the value 1 if and only if the result of the naive algorithm and that of the Strassen's algorithm are the same.
