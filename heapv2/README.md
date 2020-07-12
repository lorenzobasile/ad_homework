# Algorithmic Design homework 3: Binary Heaps
This folder contains the implementation of an array based binary heap library in which array elements are never swapped.

Moreover, it contains a short report in which theoretical questions are answered.

#### Compilation

A Makefile can be generated using the line:

```bash
cmake -G "Unix Makefiles" CMakeLists.txt
```
Afterwards, code can be compiled by executing `make`. This produces two executables: `test_delete_min` and `test_insert`, in which some functionalities of the binary heap library are tested and timed.
