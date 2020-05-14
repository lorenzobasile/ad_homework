#include "quick_sort.h"

int partition(void *A, size_t pivot, size_t left, size_t right,const size_t elem_size,total_order leq)
{

    swap(A+(pivot*elem_size),A+(left*elem_size),elem_size);
    pivot=left;
    left++;

    while(left<=right)
    {
        if(!(leq(A+(left*elem_size),A+(pivot*elem_size)))){
            swap(A+(left*elem_size),A+(right*elem_size),elem_size);
            right--;
        }
        else{
            left++;
        }
    }
        
    swap(A+(pivot*elem_size), A+(right*elem_size),elem_size);
    return right;
}

struct pair partition_ev(void *A, size_t pivot, size_t left, size_t right,const size_t elem_size,total_order leq)
{
    struct pair boundaries;
    swap(A+(pivot*elem_size),A+(left*elem_size),elem_size);
    pivot=left;
    left++;
    int rep_pivots=0;
    int loweq,greeq;
    while(left<=right)
    {
        loweq=leq(A+(left*elem_size),A+(pivot*elem_size));
        greeq=leq(A+(pivot*elem_size),A+(left*elem_size));
        if(!loweq || !greeq){//if not equal
            if(greeq){ //if bigger
                swap(A+(left*elem_size),A+(right*elem_size),elem_size);
                right--;
            }
            else{ //if smaller
                swap(A+(left*elem_size),A+((pivot-rep_pivots)*elem_size),elem_size);
                pivot=left;
                left++;
            }
        }
        else{
            pivot=left;
            left++;
            rep_pivots++;
        }
    }
        
    swap(A+(pivot*elem_size), A+(right*elem_size),elem_size);
    boundaries.r=right;
    boundaries.l=right-rep_pivots;
    return boundaries;
}

void quicksort_util(void *A, size_t left,size_t right,const size_t elem_size,total_order leq)
{
    while(left<right){
        size_t pivot = partition(A,left,left,right-1,elem_size,leq);
        quicksort_util(A,left,pivot,elem_size,leq);
        left=pivot+1;
    }
}

void quick_sort(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order leq)
{
    quicksort_util(A,0,n,elem_size,leq);
}
