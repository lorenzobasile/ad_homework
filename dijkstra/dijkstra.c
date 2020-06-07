#include "dijkstra.h"
#define MAX_VAL 2048


void init_sssp(graph G){
    for(int i=0; i<G.size; i++){
        G.V[i].d=MAX_VAL;
        G.V[i].pred=G.size;
    }
}
void relax(int* Q, int u, int v, int w, size_t queue_size){
    if(G.V[u].d+w<G.V[v]->d){
        update_distance(Q,G.V[v],G.V[u].d+w, queue_size);
        v->pred=u;
    }
}

void update_distance(int* Q, int v, int new_val, size_t queue_size){
    G.V[v].d=new_val;
    for(int i=0; i<queue_size; i++){
        if(Q[i].pred==v){
            relax(Q, v, i, new_val, queue_size);
        }
    }
}

nodearray build_queue(graph G){
    nodearray queue=malloc(sizeof(node)*G.size);
    memcpy(queue, G.V, G.size);
    return queue;
}

int extract_min(int* Q){
}

void dijkstra(graph G, node* s){
    init_sssp(G);
    *s.d=0;
    *s.pred=0;
    int* queue=malloc(sizeof(int)*G.size);
    for(int i=0; i<G.size; i++) queue[i]=i;
    queue_size=G.V;
    while(queue_size){
        int u=extract_min(Q);
        for(int i=0; i<G.size; i++){
            if(G.adj[u][i]<MAX_VAL){
                relax(queue, u, i, G.adj[u][i], queue_size);
            }
        }
}
}
