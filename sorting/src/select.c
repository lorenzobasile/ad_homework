#include "select.h"
#include "swap.h"

unsigned int select_pivot(void* A, const unsigned int n, const size_t elem_size, total_order leq);
unsigned int select_index(void* A, const unsigned int n, const unsigned int i, const size_t elem_size, total_order leq){

    if(n<=10){
        quick_sort(A,n,elem_size,leq);
        return i;
    }
    unsigned int j=select_pivot(A,n,elem_size,leq);
    struct pair bounds=partition_ev(A,j,0,n-1,elem_size,leq);
    if(i<bounds.l){
        return select_index(A,bounds.l-1,i,elem_size,leq);
    }
    if(i>bounds.r){
        return select_index(A+bounds.r*elem_size,n-bounds.r-1,i,elem_size,leq);
    }
    return i;

}

unsigned int select_pivot(void* A, const unsigned int n, const size_t elem_size, total_order leq){

    if(n<=10){
        quick_sort(A,n,elem_size,leq);
        return n/2;
    }
    unsigned int chunks=n/5, c_l;
    for(unsigned int c=0; c<chunks; c++){
        c_l=c*5;
        quick_sort(A+c_l*elem_size,5,elem_size,leq);
        swap(A+(c_l+2)*elem_size,A+c*elem_size,elem_size);
    }
    return select_index(A,chunks,chunks/2,elem_size,leq);
}


void quicksort_select_util(void *A, size_t left,size_t right,const size_t elem_size,total_order leq){

    while(left<right){
        struct pair bounds = partition_ev(A,left+select_pivot(A+left*elem_size,right-left,elem_size,leq),left,right-1,elem_size,leq);
        quicksort_select_util(A,left,bounds.l,elem_size,leq);
        left=bounds.r+1;
    }
}

void quick_sort_select(void *A, const unsigned int n, const size_t elem_size, total_order leq){
   quicksort_select_util(A,0,n,elem_size,leq);
}

