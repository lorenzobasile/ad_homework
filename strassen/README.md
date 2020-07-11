# Algorithmic Design homework 1: Strassen's Algorithm
This folder contains my implementation of Strassen's algorithm for matrix multiplication, with some modifications to generalize it to deal with rectangular matrices. The final aim of this homework is to compare the time performances of Strassen's algorithm against naive matrix multiplication algorithm when operating on rectangular matrices.

The implementation of the naive algorithm is contained in the file `matrix.c`, while `strassen.c` contains the implementation of Strassen's algorithm (in two different versions, one with optimized memory usage and one without these optimizations). The three algorithms are compared in `main.c` by running them on a set of instances.

Finally, `report.pdf` contains a small discussion about the algorithms I implemented and the results achieved.

#### Compilation

A Makefile can be produced using the following line:

```bash
cmake -G "Unix Makefiles" CMakeLists.txt
```

Once the Makefile is produced, to compile the code it is sufficient to execute `make`. This will produce an executable `strassen_test` in which Strassen's algorithm, improved Strassen's algorithm and naive matrix multiplication algorithm are tested on randomly initialized matrices of increasing sizes.