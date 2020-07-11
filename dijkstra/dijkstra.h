#ifndef _dijkstra

#define _dijkstra
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "binheap.h"
#include "graph.h"

#define MAX_VAL INT_MAX

void init_sssp(int* d, int* p, size_t size);

void relax_array(int* d, int* p, int u, int v, int w);
void dijkstra_array(graph G, int* distances, int* pred, int s);
void extractmin(int* Q, int* d, size_t* queue_size);
int isempty(size_t queue_size);
void swap(int* array, int i, int j);

void relax_heap(binheap_type* h, int*d, int* p, int u, int v, int w);
void dijkstra_heap(graph G, int* distances, int* pred, int s);

#endif
