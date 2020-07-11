#include "dijkstra.h"
#include "graph.h"
#include <time.h>
#include <stdio.h>

#define MAX_COST 100
#define EDGES_PER_NODE 5
#define REP 10

int main(){
    graph G;
    int source = 0;
    long seconds,ns;
    //external for on sizes (numbers of nodes in the graph)
    for (int i=1<<4; i<=1<<17; i*=2){
        double elapsed_a=0,elapsed_h=0;
        //internal for: 10 repetitions for each size with different graphs
        for(int j=0; j<REP; j++){
            graph_random_init(&G, i, MAX_COST, EDGES_PER_NODE);
            int* distances=malloc(sizeof(int)*G.size);
            int* distances_heap=malloc(sizeof(int)*G.size);
            int* pred=malloc(sizeof(int)*G.size);
            int* pred_heap=malloc(sizeof(int)*G.size);
            struct timespec start, finish, start2, finish2; 
            seconds = finish.tv_sec - start.tv_sec; 
            ns = finish.tv_nsec - start.tv_nsec; 
            clock_gettime(CLOCK_REALTIME, &start); 
            //call to array-based Dijkstra's algorithm
            dijkstra_array(G,distances, pred, 0);
            clock_gettime(CLOCK_REALTIME, &finish); 
            seconds = finish.tv_sec - start.tv_sec; 
            ns = finish.tv_nsec - start.tv_nsec; 
            elapsed_a += (double)seconds + (double)ns/(double)1000000000;
            clock_gettime(CLOCK_REALTIME, &start2);
            //call to heap-based Dijkstra's algorithm
            dijkstra_heap(G,distances_heap,pred_heap,0);
            clock_gettime(CLOCK_REALTIME, &finish2); 
            seconds = finish2.tv_sec - start2.tv_sec; 
            ns = finish2.tv_nsec - start2.tv_nsec; 
            elapsed_h += (double)seconds + (double)ns/(double)1000000000;
            /*for(int i=0; i<G.size; i++){
                printf("node: %d distance: %d, predecessor: %d \n", i, distances[i], pred[i]);
                printf("heap, node: %d distance: %d, predecessor: %d \n", i, distances_heap[i], pred_heap[i]);
            }*/
            deallocate_graph(&G);
            free(distances);
            free(pred);
            free(distances_heap);
            free(pred_heap);
        }
        printf("%e\n", elapsed_a/REP);
        printf("%e\n", elapsed_h/REP);
    }

    return 0;
}
