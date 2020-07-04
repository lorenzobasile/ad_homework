#include "dijkstra.h"
#include <stdio.h>
#define ADDRP(H,pos) ((H)->A+pos*(H)->key_size)

int in(ll list, int index){
    ll temp=list;
    while(temp!=NULL){
        if(temp->node==index) return 1;
        temp=temp->next;
    }
    return 0;
}

void init_sssp(int* d, int* p, int size){
    for(int i=0; i<size; i++){
        d[i]=MAX_VAL;
        p[i]=-1;
    }
}
void relax(int* d, int* p, int u, int v, int w){
    if(d[u]+w<d[v]){
        update_distance(d,v,d[u]+w);
        p[v]=u;
    }
}

void update_distance(int* d, int v, int new_val){
    d[v]=new_val;
}

int extractmin(int* Q, int* d, size_t* queue_size){
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
    return *queue_size;
}

void dijkstra(graph G, int* distances, int* pred, int s){
    int num_nodes=G.size;
    init_sssp(distances, pred, num_nodes);
    distances[s]=0;
    pred[s]=s;
    int* queue=malloc(sizeof(int)*num_nodes);
    for(int i=0; i<num_nodes; i++) queue[i]=i;
    size_t queue_size=num_nodes;
    while(queue_size>0){
        int u=extractmin(queue, distances, &queue_size);
        if(distances[queue[u]]==MAX_VAL) break;
        ll neighbour=G.adj[queue[u]];
        while(neighbour!=NULL){
            int j=neighbour->node;
            relax(distances, pred, queue[u], j, neighbour->cost);
            neighbour=neighbour->next;
    }
    }
    free(queue);
}
void swap(int* array, int i, int j){
    int temp;
    temp=array[i];
    array[i]=array[j];
    array[j]=temp;
}

void relax_heap(binheap_type* h, int* p, int u, int v, int w){
    if(*(int*)ADDRP(h,u)+w<*(int*)ADDRP(h,v)){
        int newval=*(int*)ADDRP(h,u);
        newval+=w;
        decrease_key(h, ADDRP(h, v), &newval);
        p[v]=u;
    }
}

void dijkstra_heap(graph G, int* distances, int* pred, int s){
    int num_nodes=G.size;
    init_sssp(distances, pred, num_nodes);
    distances[s]=0;
    pred[s]=s;
    binheap_type* h=build_heap((void*) distances, num_nodes, num_nodes, sizeof(int), leq_int);
    while(h->num_of_elem>0){
        if(*(int*)extract_min(h)==MAX_VAL) break;
        int u=h->key_pos[h->num_of_elem];
        ll neighbour=G.adj[u];
        while(neighbour!=NULL){
            int j=neighbour->node;
            relax_heap(h, pred, u, j, neighbour->cost);
            neighbour=neighbour->next;
        }
    }
    delete_heap(h);
}
