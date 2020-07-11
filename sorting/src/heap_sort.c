#include "heap_sort.h"
#include "binheap.h"
#include "swap.h"
#include "string.h"

void heap_sort(void *A, const unsigned int n, 
               const size_t elem_size, 
               total_order leq)
{
    //min-heap
    binheap_type* b=build_heap(A,n,n,elem_size,leq);
    //extract_min orders A in descending order
    for(unsigned int i=n-1; i>0; i--){
        extract_min(b);
    }
    //order is inverted by swapping elements
    for(unsigned int i=0; i<n/2; i++){
        swap(A+i*elem_size,A+(n-i-1)*elem_size,elem_size);
    }
}
