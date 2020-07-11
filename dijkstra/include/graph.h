#ifndef _graph
#define _graph
#include <stdlib.h>

//node of the linked list of neighbours, containing index of the node, cost of the link
//and pointer to next neighbour
typedef struct listnode{
    int node;
    int cost;
    struct listnode* next;
}listnode;

//pointer to the first element of the linked list
typedef listnode* ll;

int in(ll list, int index);

//struct graph: contains a size and an array of linked lists of neighbours
typedef struct graph {
    size_t size;
    ll* adj;
}graph;

void graph_random_init(graph* G, const size_t size, const unsigned int max_cost, const unsigned int edges_per_node);
void deallocate_graph(graph* G);

#endif
