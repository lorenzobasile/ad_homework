#include "matrix.h"
#include "stdio.h"
/*
 * this function performs the element-wise
 * subtraction of B from A and put the resulting
 * sub-matrix in C. The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void print_matrix(float const*const*const M, const size_t r, const size_t c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("%f ",M[i][j]);
        }
    printf("\n\n");
}
}
void set_to0(float** m, const size_t r, const size_t c){
    for (size_t i = 0; i < r; i++) {
        for (size_t j = 0; j < c; j++) {
            m[i][j]=0;
        }
    }
}

void sub_matrix_blocks(float **C, float const *const *const A,
                       float const *const * const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t nr, const size_t nc)
{
    for (size_t y = 0; y < nr; y++) {
      for (size_t x = 0; x < nc; x++) {
          C[y+C_f_row][x+C_f_col] =
               A[y+A_f_row][x+A_f_col] - B[y+B_f_row][x+B_f_col];
      }
    }
}

/*
 * this function performs the element-wise
 * sum of A and B and put the resulting
 * sub-matrix in C. The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void sum_matrix_blocks(float **C, float const *const *const A,
                       float const *const * const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t nr, const size_t nc)
{
    for (size_t y = 0; y < nr; y++) {
      for (size_t x = 0; x < nc; x++) {
          C[y+C_f_row][x+C_f_col] =
               A[y+A_f_row][x+A_f_col] + B[y+B_f_row][x+B_f_col];
      }
    }
}

/*
 * this function implements the naive algorithm
 * for matrix multiplication between sub-matrixes.
 * The result is placed in the sub-matrix C.
 * The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void naive_aux(float **C, float const *const *const A,
               float const *const * const B,
               const size_t C_f_row, const size_t C_f_col,
               const size_t A_f_row, const size_t A_f_col,
               const size_t B_f_row, const size_t B_f_col,
               const size_t nr_A, const size_t nc_A, const size_t nc_B)
{
  for (size_t y = 0; y < nr_A; y++) {
    for (size_t x = 0; x < nc_B; x++) {
      float value = 0.0;
      for (size_t z = 0; z < nc_A; z++) {
        value += A[y + A_f_row][z + A_f_col]*B[z + B_f_row][x + B_f_col];
      }

      C[y + C_f_row][x + C_f_col] = value;
    }
  }
}

/*
 * This function implements the Strassen's algorithm
 * for matrix multiplication between sub-matrixes.
 * The result is placed in the sub-matrix C.
 * The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
 
void strassen_aux(float **C, float const *const *const A,
                  float const *const * const B,
                  const size_t C_f_row, const size_t C_f_col,
                  const size_t A_f_row, const size_t A_f_col,
                  const size_t B_f_row, const size_t B_f_col,
                  const size_t nr_A, const size_t nc_A, const size_t nc_B)
{
    if (nr_A <= (1<<5) || nc_A <= (1<<5) || nc_B <= (1<<5) || nc_A%2 || nr_A%2 || nc_B%2 ){
        //printf("switching to naive when nr_A=%ld, nc_A=%ld, nc_B=%ld \n",nr_A, nc_A, nc_B);
        naive_aux(C, A, B,
                  C_f_row, C_f_col,
                  A_f_row, A_f_col,
                  B_f_row, B_f_col,
                  nr_A, nc_A, nc_B);

        return;
    }

    size_t nra2 = nr_A/2; // This is the size of the blocks
    size_t nca2 = nc_A/2; // This is the size of the blocks
    size_t ncb2 = nc_B/2; // This is the size of the blocks


    float ***SA = (float ***)malloc(sizeof(float **) * 5);
    for (size_t i = 0; i < 5; i++) {
        SA[i] = allocate_matrix(nra2, nca2);
    }

    float ***SB = (float ***)malloc(sizeof(float **) * 5);
    for (size_t i = 0; i < 5; i++) {
        SB[i] = allocate_matrix(nca2, ncb2);
    }

    float ***P = (float ***)malloc(sizeof(float **) * 7);
    for (size_t i = 0; i < 7; i++) {
        P[i] = allocate_matrix(nra2, ncb2);
    }

    // S1 = B12 - B22
    sub_matrix_blocks(SB[0], B, B,
                      0, 0,
                      B_f_row, B_f_col + ncb2,
                      B_f_row + nca2, B_f_col + ncb2,
                      nca2, ncb2);

    // P1 = A11 x S1
    strassen_aux(P[0], A, (const float* const *const) SB[0],
                 0, 0,
                 A_f_row, A_f_col,
                 0, 0,
                 nra2,nca2,ncb2);

    // S2 = A11 + A12
    sum_matrix_blocks(SA[1], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row, A_f_col + nca2,
                      nra2,nca2);


    // P2 = S2 x B22
    strassen_aux(P[1], (const float* const *const) SA[1], B,
                 0, 0,
                 0, 0,
                 B_f_row + nca2, B_f_col + ncb2,
                 nra2, nca2, ncb2);

    // S3 = A21 + A22
    sum_matrix_blocks(SA[1], A, A,
                      0, 0,
                      A_f_row + nra2, A_f_col,
                      A_f_row + nra2, A_f_col + nca2,
                      nra2, nca2);

    // P3 = S3 x B11
    strassen_aux(P[2], (const float* const *const) SA[1], B,
                 0, 0,
                 0, 0,
                 B_f_row, B_f_col,
                 nra2, nca2, ncb2);

    // S4 = B21 - B11
    sub_matrix_blocks(SB[1], B, B,
                      0, 0,
                      B_f_row + nca2, B_f_col,
                      B_f_row, B_f_col,
                      nca2, ncb2);

    // P4 = A22 x S4
    strassen_aux(P[3], A, (const float* const *const) SB[1],
                 0, 0,
                 A_f_row + nra2, A_f_col + nca2,
                 0, 0,
                 nra2, nca2, ncb2);

    // S5 = A11 + A22
    sum_matrix_blocks(SA[2], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + nra2, A_f_col + nca2,
                      nra2, nca2);

    // S6 = B11 + B22
    sum_matrix_blocks(SB[2], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row + nca2, B_f_col + ncb2,
                      nca2, ncb2);

    // P5 = S5 x S6
    strassen_aux(P[4], (const float* const *const) SA[2],
                 (const float* const *const) SB[2],
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2, nca2, ncb2);

    // S7 = A12 - A22
    sub_matrix_blocks(SA[3], A, A,
                      0, 0,
                      A_f_row, A_f_col + nca2,
                      A_f_row + nra2, A_f_col + nca2,
                      nra2, nca2);

    // S8 = B21 + B22
    sum_matrix_blocks(SB[3], B, B,
                      0, 0,
                      B_f_row + nca2, B_f_col,
                      B_f_row + nca2, B_f_col + ncb2,
                      nca2, ncb2);

    // P6 = S7 x S8
    strassen_aux(P[5], (const float* const *const) SA[3],
                 (const float* const *const) SB[3],
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2, nca2, ncb2);

    // S9 = A11 - A21
    sub_matrix_blocks(SA[4], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + nra2, A_f_col,
                      nra2, nca2);

    // S10 = B11 + B12
    sum_matrix_blocks(SB[4], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row, B_f_col + ncb2,
                      nca2, ncb2);

    // P7 = S9 x S10
    strassen_aux(P[6], (const float* const *const) SA[4],
                 (const float* const *const) SB[4],
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2, nca2, ncb2);

    // C11 = P5 + P4 - P2 + P6
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[3],
                      C_f_row, C_f_col,
                      0, 0,
                      0, 0,
                      nra2, ncb2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[1],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2, ncb2);
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[5],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2, ncb2);

    // C12 = P1 + P2
    sum_matrix_blocks(C, (const float* const *const) P[0],
                      (const float* const *const) P[1],
                      C_f_row, C_f_col+ncb2,
                      0, 0,
                      0, 0,
                      nra2, ncb2);

    // C21 = P3 + P4
    sum_matrix_blocks(C, (const float* const *const) P[2],
                      (const float* const *const) P[3],
                      C_f_row+nra2, C_f_col,
                      0, 0,
                      0, 0,
                      nra2, ncb2);

    // C22 = P5 + P1 - P3 - P7
    /*printf("\nP5 \n");
    print_matrix(P[4], nra2, ncb2);
    printf("\nP1 \n");
    print_matrix(P[0], nra2, ncb2);
    printf("\nP3 \n");
    print_matrix(P[2], nra2, ncb2);
    printf("\nP7 \n");
    print_matrix(P[6], nra2, ncb2);
    */
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[0],
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      0, 0,
                      nra2, ncb2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[2],
                      C_f_row+nra2, C_f_col+ncb2,
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      nra2, ncb2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[6],
                      C_f_row+nra2, C_f_col+ncb2,
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      nra2, ncb2);
    for (size_t i = 0; i < 5; i++) {
      deallocate_matrix(SA[i], nra2);
    }
    free(SA);

    for (size_t i = 0; i < 5; i++) {
      deallocate_matrix(SB[i], nca2);
    }
    free(SB);

    for (size_t i = 0; i < 7; i++) {
      deallocate_matrix(P[i], nra2);
    }
    free(P);
}
 
 
 
void strassen_imp(float **C, float const *const *const A,
                  float const *const * const B,
                  const size_t C_f_row, const size_t C_f_col,
                  const size_t A_f_row, const size_t A_f_col,
                  const size_t B_f_row, const size_t B_f_col,
                  const size_t nr_A, const size_t nc_A, const size_t nc_B)
{
    if (nr_A <= (1<<5) || nc_A <= (1<<5) || nc_B <= (1<<5) || nc_A%2 || nr_A%2 || nc_B%2 ){
        naive_aux(C, A, B,
                  C_f_row, C_f_col,
                  A_f_row, A_f_col,
                  B_f_row, B_f_col,
                  nr_A, nc_A, nc_B);

        return;
    }

    size_t nra2 = nr_A/2;
    size_t nca2 = nc_A/2;
    size_t ncb2 = nc_B/2;

    float **SA = allocate_matrix(nra2, nca2);

    float **SB = allocate_matrix(nca2, ncb2);

    float **P = allocate_matrix(nra2, ncb2);

    // S1 = B12 - B22
    sub_matrix_blocks(SB, B, B,
                      0, 0,
                      B_f_row, B_f_col + ncb2,
                      B_f_row + nca2, B_f_col + ncb2,
                      nca2, ncb2);

    // P1 = A11 x S1
    strassen_aux(P, A, (const float* const *const) SB,
                 0, 0,
                 A_f_row, A_f_col,
                 0, 0,
                 nra2,nca2,ncb2);

    // C22=P1
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2, C_f_col+ncb2,
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      nra2, ncb2);

    // S2 = A11 + A12
    sum_matrix_blocks(SA, A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row, A_f_col + nca2,
                      nra2,nca2);


    // P2 = S2 x B22
    strassen_aux(P, (const float* const *const) SA, B,
                 0, 0,
                 0, 0,
                 B_f_row + nca2, B_f_col + ncb2,
                 nra2, nca2, ncb2);
    // C12=P1(C22)+P2
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col+ncb2,
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      nra2, ncb2);
    // C11=-P2
    sub_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2, ncb2);
    // S3 = A21 + A22
    sum_matrix_blocks(SA, A, A,
                      0, 0,
                      A_f_row + nra2, A_f_col,
                      A_f_row + nra2, A_f_col + nca2,
                      nra2, nca2);

    // P3 = S3 x B11
    strassen_aux(P, (const float* const *const) SA, B,
                 0, 0,
                 0, 0,
                 B_f_row, B_f_col,
                 nra2, nca2, ncb2);
    // C21=P3
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2, C_f_col,
                      C_f_row+nra2, C_f_col,
                      0, 0,
                      nra2, ncb2);
    // C22=P1-P3
    sub_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2, C_f_col+ncb2,
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      nra2, ncb2);
                      
    // S4 = B21 - B11
    sub_matrix_blocks(SB, B, B,
                      0, 0,
                      B_f_row + nca2, B_f_col,
                      B_f_row, B_f_col,
                      nca2, ncb2);

    // P4 = A22 x S4
    strassen_aux(P, A, (const float* const *const) SB,
                 0, 0,
                 A_f_row + nra2, A_f_col + nca2,
                 0, 0,
                 nra2, nca2, ncb2);
   
    // C21=P3+P4
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2, C_f_col,
                      C_f_row+nra2, C_f_col,
                      0, 0,
                      nra2, ncb2);
                    
    // C11=P4-P2
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2, ncb2);

    // S5 = A11 + A22
    sum_matrix_blocks(SA, A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + nra2, A_f_col + nca2,
                      nra2, nca2);

    // S6 = B11 + B22
    sum_matrix_blocks(SB, B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row + nca2, B_f_col + ncb2,
                      nca2, ncb2);

    // P5 = S5 x S6
    strassen_aux(P, (const float* const *const) SA,
                 (const float* const *const) SB,
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2, nca2, ncb2);

    // C11=P5+P4-P2
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2, ncb2);

    // C22=P5+P1-P3
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2, C_f_col+ncb2,
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      nra2, ncb2);


    // S7 = A12 - A22
    sub_matrix_blocks(SA, A, A,
                      0, 0,
                      A_f_row, A_f_col + nca2,
                      A_f_row + nra2, A_f_col + nca2,
                      nra2, nca2);

    // S8 = B21 + B22
    sum_matrix_blocks(SB, B, B,
                      0, 0,
                      B_f_row + nca2, B_f_col,
                      B_f_row + nca2, B_f_col + ncb2,
                      nca2, ncb2);

    // P6 = S7 x S8
    strassen_aux(P, (const float* const *const) SA,
                 (const float* const *const) SB,
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2, nca2, ncb2);

    // C11=P6+P5+P4-P2
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2, ncb2);


    // S9 = A11 - A21
    sub_matrix_blocks(SA, A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + nra2, A_f_col,
                      nra2, nca2);

    // S10 = B11 + B12
    sum_matrix_blocks(SB, B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row, B_f_col + ncb2,
                      nca2, ncb2);

    // P7 = S9 x S10
    strassen_aux(P, (const float* const *const) SA,
                 (const float* const *const) SB,
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2, nca2, ncb2);
    
    // C22=-P7+P5+P1-P3
    sub_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2, C_f_col+ncb2,
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      nra2, ncb2);
/*
    // C11 = P5 + P4 - P2 + P6
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[3],
                      C_f_row, C_f_col,
                      0, 0,
                      0, 0,
                      nra2, ncb2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[1],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2, ncb2);
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[5],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2, ncb2);

    // C12 = P1 + P2
    sum_matrix_blocks(C, (const float* const *const) P[0],
                      (const float* const *const) P[1],
                      C_f_row, C_f_col+ncb2,
                      0, 0,
                      0, 0,
                      nra2, ncb2);

    // C21 = P3 + P4
    sum_matrix_blocks(C, (const float* const *const) P[2],
                      (const float* const *const) P[3],
                      C_f_row+nra2, C_f_col,
                      0, 0,
                      0, 0,
                      nra2, ncb2);

    // C22 = P5 + P1 - P3 - P7
    /*printf("\nP5 \n");
    print_matrix(P[4], nra2, ncb2);
    printf("\nP1 \n");
    print_matrix(P[0], nra2, ncb2);
    printf("\nP3 \n");
    print_matrix(P[2], nra2, ncb2);
    printf("\nP7 \n");
    print_matrix(P[6], nra2, ncb2);
    
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[0],
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      0, 0,
                      nra2, ncb2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[2],
                      C_f_row+nra2, C_f_col+ncb2,
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      nra2, ncb2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[6],
                      C_f_row+nra2, C_f_col+ncb2,
                      C_f_row+nra2, C_f_col+ncb2,
                      0, 0,
                      nra2, ncb2);
    */
    deallocate_matrix(SA, nra2);



    deallocate_matrix(SB, nca2);

    deallocate_matrix(P, nra2);

}


/*
 * this functions is exclusively meant to provide an
 * easy to use API
 */
void strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B, size_t nr_A, size_t nc_A, size_t nc_B)
{

  strassen_aux(C, A, B,
               0, 0,
               0, 0,
               0, 0,
               nr_A, nc_A, nc_B);

}
void strassen_improved(float **C, float const *const *const A,
                                    float const *const *const B, size_t nr_A, size_t nc_A, size_t nc_B)
{
  set_to0(C, nr_A, nc_B); 
  strassen_imp(C, A, B,
               0, 0,
               0, 0,
               0, 0,
               nr_A, nc_A, nc_B);

}

