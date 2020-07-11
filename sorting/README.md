# Algorithmic Design homework 4 and 5: Sorting
This folder contains the solution to homework 4 and 5 of the course of Algorithmic Design. The code of different sorting algorithms can be found in the subfolder `src`, while the corresponding headers are in `include`.

Moreover, there are two short reports, `report1.pdf` and `report2.pdf`, which contain the solutions to the theoretical questions respectively of homework 4 and homework 5.

#### Compilation

To correctly compile the code present in this folder, it is useful to produce a Makefile by typing:

```bash
cmake -G "Unix Makefiles" -DBINHEAP_PATH=<BINHEAP_INSTALL_DIR> CMakeLists.txt
```

Where `<BINHEAP_INSTALL_DIR>` is the directory in which the binary heap library of homework 2 is present.

After this, executing `make` will produce an executable `test_sorting` in which all sorting algorithms are tested on randomly initialized arrays of different sizes and whose time results are shown in the report files.