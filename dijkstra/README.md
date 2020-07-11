# Algorithmic Design homework 6: Dijkstra's Algorithm
Array based and heap based versions of Dijkstra's algorithm are implemented by the functions `dijkstra_array` and `dijkstra_heap ` that can be found in source file `dijkstra.c`, while the file `graph.c` contains the utilities needed to initialize and correctly deallocate a graph. `main.c` contains the code needed to test the two implementation of Dijkstra's algorithm on a set of instances.

Moreover, in this folder there is a `report.pdf`, in which some experimental results are shown.

#### Compilation

To correctly compile the code present in this folder, it is useful to produce a Makefile by typing:

```bash
cmake -G "Unix Makefiles" -DBINHEAP_PATH=<BINHEAP_INSTALL_DIR> CMakeLists.txt
```

Where `<BINHEAP_INSTALL_DIR>` is the path to the directory in which the binary heap library of homework 3 is present (in this repository, `heapv2`).

After this, executing `make` will produce an executable `dijkstra` in which both versions of Dijkstra's algorithm are tested and timed on randomly initialized graphs of different sizes.