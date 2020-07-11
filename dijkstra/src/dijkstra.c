#include "dijkstra.h"

//initialization function: taken an array of distances d and an array of predecessors p, sets all distances
//to MAX_VAL and all predecessors to -1
void init_sssp(int* d, int* p, size_t size){
    for(int i=0; i<size; i++){
        d[i]=MAX_VAL;
        p[i]=-1;
    }
}

//function that is verifies if the distance of a node is to be updated when one of its neighbours is extracted
//from the queue and, if this is the case, updates distance and sets as predecessor the newly extracted node
void relax_array(int* d, int* p, int u, int v, int w){
    if(d[u]+w<d[v]){
        d[v]=d[u]+w;
        p[v]=u;
    }
}

//function used to extract the node with minimal distance from an array of node indexes
void extractmin(int* Q, int* d, size_t* queue_size){
    int argmin;
    int min=MAX_VAL;
    for(int i=0; i<*queue_size; i++){
        if(d[Q[i]]<min){
            min=d[Q[i]];
            argmin=i;
        }
    }
    swap(Q,argmin,*queue_size-1);
    (*queue_size)--;
}

//array based implementation of Dijkstra's algorithm
void dijkstra_array(graph G, int* distances, int* pred, int s){
    size_t num_nodes=G.size;
    init_sssp(distances, pred, num_nodes);
    distances[s]=0;
    pred[s]=s;
    int* queue=malloc(sizeof(int)*num_nodes);
    for(int i=0; i<num_nodes; i++) queue[i]=i;
    size_t queue_size=num_nodes;
    double total=0;
    while(queue_size>0){
        extractmin(queue, distances, &queue_size);
        if(distances[queue[queue_size]]==MAX_VAL) break;
        ll neighbour=G.adj[queue[queue_size]];
        while(neighbour!=NULL){
            int j=neighbour->node;
            relax_array(distances, pred, queue[queue_size], j, neighbour->cost);
            neighbour=neighbour->next;
    }
    }
    free(queue);
}

//basic function to swap two indexes in an array of integers
void swap(int* array, int i, int j){
    int temp;
    temp=array[i];
    array[i]=array[j];
    array[j]=temp;
}

//heap based version of relax. now the update of the distance is performed by decrease_key
void relax_heap(binheap_type* h, int* d, int* p, int u, int v, int w){
    if(d[u]+w<d[v]){
        int newval=d[u];
        newval+=w;
        decrease_key(h, (void*) &d[v], &newval);
        p[v]=u;
    }
}

//heap based implementation of Dijkstra's algorithm
void dijkstra_heap(graph G, int* distances, int* pred, int s){
    size_t num_nodes=G.size;
    init_sssp(distances, pred, num_nodes);
    distances[s]=0;
    pred[s]=s;
    binheap_type* h=build_heap((void*) distances, num_nodes, num_nodes, sizeof(int), leq_int);
    while(!is_heap_empty(h)){
        const int* temp=(int*)extract_min(h);
        if(*temp==MAX_VAL) break;
        int u=temp-distances;
        ll neighbour=G.adj[u]; 
        while(neighbour!=NULL){
            int j=neighbour->node;
            relax_heap(h, distances, pred, u, j, neighbour->cost);
            neighbour=neighbour->next;
        }
    }
    delete_heap(h);
}
