#ifndef _dijkstra

#define _dijkstra
#include <string.h>
#include <stdlib.h>

typedef struct{
    int d;
    int pred;
    int name;
}node;
typedef node* nodearray;

typedef struct {
    nodearray V;
    size_t size;
    int** adj;
}graph;

void init_sssp(graph G);
void relax(nodearray queue, int u, int v, int w, size_t queue_size);
void dijkstra(graph G, int s);
void update_distance(nodearray Q, int v, int new_val, size_t queue_size);
nodearray build_queue(graph G);
int extract_min(nodearray Q, size_t* queue_size);
int isempty(size_t queue_size);
void swap(nodearray, int, int);
void print_node(node n);

#endif
