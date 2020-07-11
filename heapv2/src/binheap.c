#include <binheap.h>
#include <string.h>
#include <stdio.h> 

#define PARENT(node) ((node-1)/2)
#define LEFT_CHILD(node) (2*(node)+1)
#define RIGHT_CHILD(node) (2*(node+1))
#define VALID_NODE(H,node) ((H)->num_of_elem>(node))
#define ADDR(H,node) ((H)->A+H->key_pos[node]*(H)->key_size)
#define INDEX_OF(H,addr) H->rev_pos[(((addr)-((H)->A))/(H)->key_size)]


int is_heap_empty(const binheap_type *H)
{
    return H->num_of_elem==0;
}


const void *min_value(const binheap_type *H)
{
    if(is_heap_empty(H)) return NULL;
   return ADDR(H,0);
}


void swap_keys(binheap_type *H, unsigned int n_a, unsigned int n_b)
{
    //key_pos stores the position of the i-th key in the array A
    //ex: key_pos[0] contains the position of the root in A
    unsigned int temp=H->key_pos[n_a];
    H->key_pos[n_a]=H->key_pos[n_b];
    H->key_pos[n_b]=temp; 
    //rev_pos stores the position in the heap of the i-th element of array A
    //ex: rev_pos[0] contains the position of the first element of A in the structure of the heap
    temp=H->rev_pos[H->key_pos[n_a]];
    H->rev_pos[H->key_pos[n_a]]=H->rev_pos[H->key_pos[n_b]];
    H->rev_pos[H->key_pos[n_b]]=temp;

}


//iterative version
void heapify(binheap_type *H,unsigned int node)
{
    unsigned int dst_node=node, child;
    do
    {
        node=dst_node;
        child=RIGHT_CHILD(node);
        if(VALID_NODE(H,child) && H->leq(ADDR(H,child), ADDR(H,dst_node))) dst_node=child;
        child=LEFT_CHILD(node);
        if(VALID_NODE(H,child) && H->leq(ADDR(H,child), ADDR(H,dst_node))) dst_node=child;
        if(dst_node!=node) swap_keys(H,dst_node,node);
    } while(dst_node != node);
}


const void *extract_min(binheap_type *H)
{
    if(is_heap_empty(H)) return NULL;
    swap_keys(H,0, H->num_of_elem-1);
    H->num_of_elem--;
    heapify(H,0);
    return ADDR(H,H->num_of_elem);
}


const void *find_the_max(void *A,const unsigned int num_of_elem,const size_t key_size,total_order_type leq)
{
    if(num_of_elem==0) return NULL;
    const void *max_value=A;
    for(const void *addr=A+key_size;addr!=A+num_of_elem*key_size;addr+=key_size){
        if(!leq(addr,max_value)) max_value=addr;
    }
    return max_value;
}


binheap_type *build_heap(void *A,const unsigned int num_of_elem,const unsigned int max_size,const size_t key_size,total_order_type leq)
{
    binheap_type *H=(binheap_type*)malloc(sizeof(binheap_type));
    H->A=A;
    H->key_pos=malloc(sizeof(int)*max_size);
    H->rev_pos=malloc(sizeof(int)*max_size);
    H->num_of_elem=num_of_elem;
    H->max_size=max_size;
    H->key_size=key_size;
    H->leq=leq;
    H->max_order_value=malloc(key_size);
    if(num_of_elem==0) return H;
    //initializing both key_pos and rev_pos with i
    for(unsigned int i=0; i<num_of_elem; i++){
        H->key_pos[i]=i;
        H->rev_pos[i]=i;
    }
    const void *value=find_the_max(A,num_of_elem,key_size,leq);
    memcpy(H->max_order_value, value, key_size);
    for(unsigned int i=num_of_elem/2;i>0;i--) heapify(H,i);
    heapify(H,0);
    return H;
}


void delete_heap(binheap_type *H)
{
    free(H->max_order_value);
    free(H->key_pos);
    free(H->rev_pos);
    free(H);
}

const void *decrease_key(binheap_type *H, void *node, const void *value)
{
    int node_idx=INDEX_OF(H,node);
    if(!VALID_NODE(H,node_idx) || !(H->leq(value,node))) return NULL;
    //if key is smaller than the one in node, store it in node
    memcpy(node, value, H->key_size);
    int parent_idx=H->num_of_elem>1?PARENT(node_idx):0; 
    //if the heap has only the root the index of the parent is 0
    void *parent=ADDR(H,parent_idx);
    //iterate until parent key is bigger than node key
    while((node_idx!=0) && !H->leq(parent,node))
    {
        //swap node and parent
        swap_keys(H,parent_idx,node_idx);
        //set node index to parent index
        node_idx=parent_idx;
        parent_idx=node_idx?PARENT(node_idx):0;
        parent=ADDR(H,parent_idx);
    }
    return node;
}

const void *insert_value(binheap_type *H, const void *value)
{
    //cannot insert, heap is full
    if(H->max_size==H->num_of_elem) return NULL;
    // update (if needed) max_order_value
    if(H->num_of_elem==0 || !H->leq(value,H->max_order_value)) memcpy(H->max_order_value,value,H->key_size);
    //initializing key_pos for the new element
    H->key_pos[H->num_of_elem]=H->num_of_elem;
    //same for rev_pos
    H->rev_pos[H->num_of_elem]=H->num_of_elem;
    void *new_node_addr=ADDR(H,H->num_of_elem);
    //putting max_order_value in the last node
    memcpy(new_node_addr,H->max_order_value,H->key_size);
    H->num_of_elem++;
    //decreasing key to the desired value
    return decrease_key(H,new_node_addr,value);
}


void print_heap(const binheap_type *H, 
                void (*key_printer)(const void *value))
{

    unsigned int next_level_node=1;
    for(unsigned int node=0;node<H->num_of_elem;node++){
        if(node==next_level_node){
            printf("\n");
            next_level_node=LEFT_CHILD(node);
        }
        else printf("\t");
        key_printer(ADDR(H,node));
    }
    printf("\n");
}
