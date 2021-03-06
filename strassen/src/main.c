#include <stdio.h>

#include "test.h"
#include "matrix.h"
#include "strassen.h"


int main(int argc, char *argv[]) {
  size_t n =(1<<11)+1;


  float **A = allocate_random_matrix(n, n);
  float **B = allocate_random_matrix(n, n);
  float **C0 = allocate_matrix(n, n);
  float **C1 = allocate_matrix(n, n);
  float **C2 = allocate_matrix(n, n);

  //test of Strassen's algorithm and improved Strassen's algorithm against naive matrix multiplication
  //on rectangular matrices
  printf("Strassen's Alg.\tImproved Alg.\tNaive Alg.\tSame results\t sizes: NxM,MxP\n");
  for (size_t j = 1<<4; j <= n; j *= 2) {
    
    printf("%lf\t", test(strassen_matrix_multiplication, C2, A, B, j-1, j,j+1));
    fflush(stdout);
    printf("%lf\t", test(strassen_improved, C1, A, B, j-1, j,j+1));
    fflush(stdout);
    printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, j-1, j, j+1));
    fflush(stdout);
    printf("%d\t\t ", 
        same_matrix((float const *const *const)C1, (float const *const *const)C2, j-1, j+1) &&
        same_matrix((float const *const *const)C0, (float const *const *const)C2, j-1, j+1) &&
        same_matrix((float const *const *const)C1, (float const *const *const)C0, j-1, j+1) );
    fflush(stdout);  
    printf("%ldx%ld, %ldx%ld\n", j-1,j,j,j+1);
    fflush(stdout);
  }

  deallocate_matrix(A, n);
  deallocate_matrix(B, n);
  deallocate_matrix(C0, n);
  deallocate_matrix(C1, n);
  deallocate_matrix(C2, n);

  return 0;
}
