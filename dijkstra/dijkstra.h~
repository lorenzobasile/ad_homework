#ifndef _dijkstra

#define _dijkstra
#include <string.h>
#include <stdlib.h>
typedef struct{
    int d;
    size_t pred;
}node;
typedef node* nodearray;

typedef struct {
    nodearray V;
    size_t size;
    int** adj;
}graph;

void init_sssp(graph G);
void relax(int* queue, int u, int v, int w, size_t queue_size);
void dijkstra(graph G, node* s);
void update_distance(int* Q, int v, int new_val, size_t queue_size);
nodearray build_queue(graph G);
node extract_min(int* Q);

#endif
