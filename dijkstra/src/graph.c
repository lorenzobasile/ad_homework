#include "graph.h"

//simple boolean function to verify if a node is present in an adjacency list
int in(ll list, int index){
    ll temp=list;
    while(temp!=NULL){
        if(temp->node==index) return 1;
        temp=temp->next;
    }
    return 0;
}

//function to randomly initialize a graph, taken in input the number of nodes, the maximum cost of an edge
//and the average number of neighbours per node
void graph_random_init(graph* G, const size_t size, const unsigned int max_cost, const unsigned int num_of_neighbours){
    G->size = size;
    //allocating the array of linked adjacency lists
    G->adj = malloc(sizeof(ll)*G->size);
    for(int i=0; i<G->size; i++){
        G->adj[i]=NULL;
        ll temp;
        //sampling the number of neighbours of node i
        int neighbours=rand()%(2*num_of_neighbours);
        for(int j=0; j<num_of_neighbours; j++){
            //allocating nodes of the linked adjacency list
            temp=malloc(sizeof(listnode));
            //do-while loop is needed to avoid multiple edges between the same nodes and self loops
            int candidate;
            do{
                candidate=rand()%G->size;
            } while(candidate==i || in(G->adj[i], candidate));
            temp->node=candidate;
            //sampling the cost of the edge
            temp->cost=rand()%max_cost;
            temp->next=G->adj[i];
            //moving head of the linked list
            G->adj[i]=temp;
        }
        /*temp=G->adj[i];
        while(temp!=NULL){
            printf("%d -> %d, cost: %d \n", i, temp->node, temp->cost);
            temp=temp->next;
        }*/
    }
}

//function to deallocate a graph. all the nodes in the adjacency lists are properly deallocated and finally
//the array of linked lists is deallocated itself
void deallocate_graph(graph* G){
    listnode* temp,*temp2;
    for(int i=0; i<G->size; i++){
        temp=G->adj[i];
        while(temp!=NULL){
            temp2=temp;
            temp=temp->next;
            free(temp2);
        }
    }
    free(G->adj);
}
