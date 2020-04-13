#include <stdio.h>

#include "test.h"
#include "matrix.h"
#include "strassen.h"


int main(int argc, char *argv[]) {
  size_t n = 1 << 12;
  //size_t n=16;

  float **A = allocate_random_matrix(n, n);
  float **B = allocate_random_matrix(n, n);
  float **C0 = allocate_matrix(n, n);
  float **C1 = allocate_matrix(n, n);
  float **C2 = allocate_matrix(n, n);
  //set_to0(C0,n,n);
  //set_to0(C1,n,n);
  //set_to0(C2,n,n);
  
  printf("n\tStrassen's Alg.\tImproved Alg.\tNaive Alg.\tSame result\n");
  for (size_t j = 4; j <= n; j *= 2) {
    //set_to0(C1,n,n);
    printf("%ld\t", j);
    fflush(stdout);
    printf("%lf\t", test(strassen_matrix_multiplication, C2, A, B, n/2, j,n/4));
    fflush(stdout);
    printf("%lf\t", test(strassen_improved, C1, A, B, n/2, j,n/4));
    fflush(stdout);
    printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, n/2, j, n/4));
    //print_matrix(C0, n/2, n/4);
    //printf("\n");
    //print_matrix(C1, n/2, n/4);
    //print_matrix(C0, n/2, n/4)
    //printf("%f",A[0][0]);
    //printf("\nA \n");
    //print_matrix((float const *const *const)A,2,j);
    //printf("\nB \n");
    //print_matrix((float const *const *const)B,j,4);
    //printf("\nC0 \n");
    //print_matrix((float const *const *const)C0,2,4);
    //printf("\nC1 \n");
    //print_matrix((float const *const *const)C1,2,4);

    fflush(stdout);

    printf("%d\n", same_matrix((float const *const *const)C0,
                               (float const *const *const)C1, n/2, n/4));
  }

  deallocate_matrix(A, n);
  deallocate_matrix(B, n);
  deallocate_matrix(C0, n);
  deallocate_matrix(C1, n);

  return 0;
}
