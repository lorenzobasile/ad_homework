#include "dijkstra.h"
#include <time.h>
#include <stdio.h>

#define MAX_COST 10

int main(){
    graph G;
    int source = 0;
    for (int i=2; i<(1<<13); i*=2){
        G.size = i;
        G.adj = malloc(sizeof(ll)*G.size);
        int* distances=malloc(sizeof(int)*G.size);
        int* distances_heap=malloc(sizeof(int)*G.size);
        int* pred=malloc(sizeof(int)*G.size);
        int* pred_heap=malloc(sizeof(int)*G.size);
        for(int i=0; i<G.size; i++){
            G.adj[i]=NULL;
            int num_of_neighbours=rand()%(G.size-1);
            ll temp;
            for(int j=0; j<num_of_neighbours; j++){
                temp=malloc(sizeof(listnode));
                int candidate;
                do{
                    candidate=rand()%G.size;
                }
                while(candidate==i || in(G.adj[i], candidate));
                temp->node=candidate;
                temp->cost=rand()%MAX_COST;
                temp->next=G.adj[i];
                G.adj[i]=temp;
            }
            temp=G.adj[i];
            while(temp!=NULL){
                //printf("%d -> %d, cost: %d \n", i, temp->node, temp->cost);
                temp=temp->next;
            }
        
        }
    struct timespec start, finish; 
    clock_gettime(CLOCK_REALTIME, &start); 

    dijkstra(G,distances, pred, 0);
    
    /*for(int i=0; i<G.size; i++){
        printf("node: %d distance: %d, predecessor: %d \n", i, distances[i], pred[i]);
        printf("heap, node: %d distance: %d, predecessor: %d \n", i, distances_heap[i], pred_heap[i]);
    }*/

    clock_gettime(CLOCK_REALTIME, &finish); 

    long seconds = finish.tv_sec - start.tv_sec; 
    long ns = finish.tv_nsec - start.tv_nsec; 
    
    printf("size=%d, total seconds: %e\n",i, (double)seconds + (double)ns/(double)1000000000);
    
    clock_gettime(CLOCK_REALTIME, &start); 
    
    dijkstra_heap(G,distances_heap,pred_heap,0);
    
    clock_gettime(CLOCK_REALTIME, &finish); 

    seconds = finish.tv_sec - start.tv_sec; 
    ns = finish.tv_nsec - start.tv_nsec; 
    
    printf("size=%d, total seconds: %e\n",i, (double)seconds + (double)ns/(double)1000000000);
    
        for(int i=0; i<G.size; i++){
        }
        for(int i=0; i<G.size; i++){
            free(G.adj[i]);
        }
        free(G.adj);
        free(distances);
        free(pred);
    }

    return 0;
}
