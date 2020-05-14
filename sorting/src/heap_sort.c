#include "heap_sort.h"
#include "binheap.h"
#include "string.h"

void int_printer(const void *value)
{
  printf("%d", *((const int *)value));
}


void heap_sort(void *A, const unsigned int n, 
               const size_t elem_size, 
               total_order leq)
{
    binheap_type* b=build_heap(A,n,n,elem_size,geq_int); 
    for(unsigned int i=n-1; i>0; i--){
        extract_min(b);
    }
}
