#ifndef _dijkstra

#define _dijkstra
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "binheap.h"

#define MAX_VAL INT_MAX

typedef struct listnode{
    int node;
    int cost;
    struct listnode* next;
}listnode;

typedef listnode* ll;

int in(ll list, int index);

typedef struct graph {
    size_t size;
    ll* adj;
}graph;


void init_sssp(int* d, int* p, int size);
void relax(int* d, int* p, int u, int v, int w);
void dijkstra(graph G, int* distances, int* pred, int s);
void update_distance(int* d, int v, int new_val);
int extractmin(int* Q, int* d, size_t* queue_size);
int isempty(size_t queue_size);
void swap(int* array, int i, int j);

void relax_heap(binheap_type* h, int* p, int u, int v, int w);
void dijkstra_heap(graph G, int* distances, int* pred, int s);

#endif
