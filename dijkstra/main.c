#include "dijkstra.h"
#include <stdio.h>

int main(){
    graph G;
    int source = 0;
    G.size = 5;
    G.V = malloc(sizeof(node)*G.size);
    G.adj = malloc(sizeof(int*)*G.size);
    for(int i=0; i<G.size; i++){
        G.V[i].name=i;
        G.adj[i] = calloc(sizeof(int),G.size);
    }
    G.adj[0][1] = 3;
    G.adj[1][2] = 2;
    G.adj[2][3] = 6;
    G.adj[0][4] = 5;
    G.adj[4][3] = 8;
    dijkstra(G,0);

    for(int i=0; i<G.size; i++){
        printf("node: %d, distance: %d\n",G.V[i].name, G.V[i].d);
    }

    return 0;
}
