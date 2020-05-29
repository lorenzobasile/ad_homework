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
void reset(float** m, const size_t nr, const size_t nc){
    sub_matrix_blocks(m, (const float* const *const) m, (const float* const *const) m, 0,0,0,0,0,0,nr,nc);
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
    if (nr_A <= (1<<5) || nc_A <= (1<<5) || nc_B <= (1<<5)){
        naive_aux(C, A, B,
                  C_f_row, C_f_col,
                  A_f_row, A_f_col,
                  B_f_row, B_f_col,
                  nr_A, nc_A, nc_B);

        return;
    }
    size_t nra2r = nr_A/2+nr_A%2; // This is the size of the blocks
    size_t nca2r = nc_A/2+nc_A%2; // This is the size of the blocks
    size_t ncb2r = nc_B/2+nc_B%2; // This is the size of the blocks
    size_t nra2 = nr_A/2; // This is the size of the blocks
    size_t nca2 = nc_A/2; // This is the size of the blocks
    size_t ncb2 = nc_B/2; // This is the size of the blocks


    float ***SA = (float ***)malloc(sizeof(float **) * 5);
    for (size_t i = 0; i < 5; i++) {
        SA[i] = allocate_matrix(nra2r, nca2r);
    }

    float ***SB = (float ***)malloc(sizeof(float **) * 5);
    for (size_t i = 0; i < 5; i++) {
        SB[i] = allocate_matrix(nca2r, ncb2r);
    }

    float ***P = (float ***)malloc(sizeof(float **) * 7);
    for (size_t i = 0; i < 7; i++) {
        P[i] = allocate_matrix(nra2r, ncb2r);
    }

    // S1 = B12 - B22
    sum_matrix_blocks(SB[0], (const float* const *const) SB[0], B,
                      0, 0,
                      0,0,
                      B_f_row, B_f_col + ncb2r,
                      nca2r,ncb2);
    sub_matrix_blocks(SB[0], (const float* const *const) SB[0], B,
                      0, 0,
                      0, 0,
                      B_f_row + nca2r, B_f_col + ncb2r,
                      nca2, ncb2);


    // P1 = A11 x S1
    strassen_aux(P[0], A, (const float* const *const) SB[0],
                 0, 0,
                 A_f_row, A_f_col,
                 0, 0,
                 nra2r,nca2r,ncb2r);

    // S2 = A11 + A12
    sum_matrix_blocks(SA[0], (const float* const *const) SA[0], A,
                      0, 0,
                      0, 0,
                      A_f_row, A_f_col,
                      nra2r,nca2r);
    sum_matrix_blocks(SA[0], (const float* const *const) SA[0], A,
                      0, 0,
                      0, 0,
                      A_f_row, A_f_col + nca2r,
                      nra2r,nca2);
    //B22+padding
    float** temp=allocate_matrix(nca2r,ncb2r);
    sum_matrix_blocks(temp,(const float* const *const) temp,B,
                      0, 0,
                      0, 0,
                      B_f_row+nca2r, B_f_col+ncb2r,
                      nca2, ncb2);
    // P2 = S2 x B22
    strassen_aux(P[1], (const float* const *const) SA[0], (const float* const *const) temp,
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2r, nca2r, ncb2r);
      
    // S3 = A21 + A22
    sum_matrix_blocks(SA[1], (const float* const *const) SA[1], A,
                      0, 0,
                      0, 0,
                      A_f_row+nra2r, A_f_col,
                      nra2,nca2r);
    sum_matrix_blocks(SA[1], (const float* const *const) SA[1], A,
                      0, 0,
                      0, 0,
                      A_f_row + nra2r, A_f_col + nca2r,
                      nra2, nca2);

    // P3 = S3 x B11
    strassen_aux(P[2], (const float* const *const) SA[1], B,
                 0, 0,
                 0, 0,
                 B_f_row, B_f_col,
                 nra2r, nca2r, ncb2r);


    // S4 = B21 - B11
    sum_matrix_blocks(SB[1], (const float* const *const) SB[1], B,
                      0, 0,
                      0, 0,
                      B_f_row + nca2r, B_f_col,
                      nca2,ncb2r);
    sub_matrix_blocks(SB[1], (const float* const *const) SB[1], B,
                      0, 0,
                      0, 0,
                      B_f_row, B_f_col,
                      nca2r, ncb2r);
    //A22+padding
    deallocate_matrix(temp,nca2r);
    temp=allocate_matrix(nra2r,nca2r);
    sum_matrix_blocks(temp,(const float* const *const) temp,A,
                      0, 0,
                      0, 0,
                      A_f_row+nra2r, A_f_col+nca2r,
                      nra2, nca2);
    // P4 = A22 x S4
    strassen_aux(P[3], (const float* const *const) temp, (const float* const *const) SB[1],
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2r, nca2r, ncb2r);

    // S5 = A11 + A22
    sum_matrix_blocks(SA[2], (const float* const *const) SA[2], A,
                      0, 0,
                      0, 0,
                      A_f_row, A_f_col,
                      nra2r,nca2r);
    sum_matrix_blocks(SA[2], (const float* const *const) SA[2], A,
                      0, 0,
                      0, 0,
                      A_f_row + nra2r, A_f_col + nca2r,
                      nra2, nca2);

    // S6 = B11 + B22
    sum_matrix_blocks(SB[2], (const float* const *const) SB[2], B,
                      0, 0,
                      0, 0,
                      B_f_row, B_f_col,
                      nca2r,ncb2r);
    sum_matrix_blocks(SB[2], (const float* const *const) SB[2], B,
                      0, 0,
                      0, 0,
                      B_f_row + nca2r, B_f_col + ncb2r,
                      nca2, ncb2);

    // P5 = S5 x S6
    strassen_aux(P[4], (const float* const *const) SA[2],
                 (const float* const *const) SB[2],
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2r, nca2r, ncb2r);

    // S7 = A12 - A22
    sum_matrix_blocks(SA[3], (const float* const *const) SA[3], A,
                      0, 0,
                      0, 0,
                      A_f_row, A_f_col + nca2r,
                      nra2r,nca2);
    sub_matrix_blocks(SA[3], (const float* const *const) SA[3], A,
                      0, 0,
                      0, 0,
                      A_f_row + nra2r, A_f_col + nca2r,
                      nra2, nca2);

    // S8 = B21 + B22
    sum_matrix_blocks(SB[3], (const float* const *const) SB[3], B,
                      0, 0,
                      0, 0,
                      B_f_row + nca2r, B_f_col,
                      nca2,ncb2r);
    sum_matrix_blocks(SB[3], (const float* const *const) SB[3], B,
                      0, 0,
                      0, 0,
                      B_f_row + nca2r, B_f_col + ncb2r,
                      nca2, ncb2);

    // P6 = S7 x S8
    strassen_aux(P[5], (const float* const *const) SA[3],
                 (const float* const *const) SB[3],
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2r, nca2r, ncb2r);

    // S9 = A11 - A21
    sum_matrix_blocks(SA[4], (const float* const *const) SA[4], A,
                      0, 0,
                      0, 0,
                      A_f_row, A_f_col,
                      nra2r,nca2r);
    sub_matrix_blocks(SA[4], (const float* const *const) SA[4], A,
                      0, 0,
                      0, 0,
                      A_f_row + nra2r, A_f_col,
                      nra2, nca2r);

    // S10 = B11 + B12
    sum_matrix_blocks(SB[4], (const float* const *const) SB[4], B,
                      0, 0,
                      0, 0,
                      B_f_row, B_f_col,
                      nca2r,ncb2r);         
    sum_matrix_blocks(SB[4], (const float* const *const) SB[4], B,
                      0, 0,
                      0, 0,
                      B_f_row, B_f_col + ncb2r,
                      nca2r, ncb2);

    // P7 = S9 x S10
    strassen_aux(P[6], (const float* const *const) SA[4],
                 (const float* const *const) SB[4],
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2r, nca2r, ncb2r);

    // C11 = P5 + P4 - P2 + P6
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[3],
                      C_f_row, C_f_col,
                      0, 0,
                      0, 0,
                      nra2r, ncb2r);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[1],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2r, ncb2r);
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[5],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2r, ncb2r);

    // C12 = P1 + P2
    sum_matrix_blocks(C, (const float* const *const) P[0],
                      (const float* const *const) P[1],
                      C_f_row, C_f_col+ncb2r,
                      0, 0,
                      0, 0,
                      nra2r, ncb2);

    // C21 = P3 + P4
    sum_matrix_blocks(C, (const float* const *const) P[2],
                      (const float* const *const) P[3],
                      C_f_row+nra2r, C_f_col,
                      0, 0,
                      0, 0,
                      nra2, ncb2r);

    // C22 = P5 + P1 - P3 - P7
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[0],
                      C_f_row+nra2r, C_f_col+ncb2r,
                      0, 0,
                      0, 0,
                      nra2, ncb2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[2],
                      C_f_row+nra2r, C_f_col+ncb2r,
                      C_f_row+nra2r, C_f_col+ncb2r,
                      0, 0,
                      nra2, ncb2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[6],
                      C_f_row+nra2r, C_f_col+ncb2r,
                      C_f_row+nra2r, C_f_col+ncb2r,
                      0, 0,
                      nra2, ncb2);
    for (size_t i = 0; i < 5; i++) {
      deallocate_matrix(SA[i], nra2r);
    }
    free(SA);

    for (size_t i = 0; i < 5; i++) {
      deallocate_matrix(SB[i], nca2r);
    }
    free(SB);

    for (size_t i = 0; i < 7; i++) {
      deallocate_matrix(P[i], nra2r);
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
    if (nr_A <= (1<<5) || nc_A <= (1<<5) || nc_B <= (1<<5)){
        naive_aux(C, A, B,
                  C_f_row, C_f_col,
                  A_f_row, A_f_col,
                  B_f_row, B_f_col,
                  nr_A, nc_A, nc_B);

        return;
    }
    reset(C,nr_A,nc_B);
    size_t nra2r = nr_A/2+nr_A%2; // This is the size of the blocks
    size_t nca2r = nc_A/2+nc_A%2; // This is the size of the blocks
    size_t ncb2r = nc_B/2+nc_B%2; // This is the size of the blocks
    size_t nra2 = nr_A/2; // This is the size of the blocks
    size_t nca2 = nc_A/2; // This is the size of the blocks
    size_t ncb2 = nc_B/2; // This is the size of the blocks
    
    float **SA = allocate_matrix(nra2r, nca2r);

    float **SB = allocate_matrix(nca2r, ncb2r);

    float **P = allocate_matrix(nra2r, ncb2r);

    // S1 = B12 - B22
    sum_matrix_blocks(SB, (const float* const *const) SB, B,
                      0, 0,
                      0,0,
                      B_f_row, B_f_col + ncb2r,
                      nca2r,ncb2);
    sub_matrix_blocks(SB, (const float* const *const) SB, B,
                      0, 0,
                      0, 0,
                      B_f_row + nca2r, B_f_col + ncb2r,
                      nca2, ncb2);


    // P1 = A11 x S1
    strassen_imp(P, A, (const float* const *const) SB,
                 0, 0,
                 A_f_row, A_f_col,
                 0, 0,
                 nra2r,nca2r,ncb2r);

    // C22=P1
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2r, C_f_col+ncb2r,
                      C_f_row+nra2r, C_f_col+ncb2r,
                      0, 0,
                      nra2, ncb2);    
    // C12=P1
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col+ncb2r,
                      C_f_row, C_f_col+ncb2r,
                      0, 0,
                      nra2r, ncb2);
    // S2 = A11 + A12
    sum_matrix_blocks(SA, (const float* const *const) SA, A,
                      0, 0,
                      0, 0,
                      A_f_row, A_f_col,
                      nra2r,nca2r);
    sum_matrix_blocks(SA, (const float* const *const) SA, A,
                      0, 0,
                      0, 0,
                      A_f_row, A_f_col + nca2r,
                      nra2r,nca2);
    //B22+padding
    float** temp=allocate_matrix(nca2r,ncb2r);
    sum_matrix_blocks(temp,(const float* const *const) temp,B,
                      0, 0,
                      0, 0,
                      B_f_row+nca2r, B_f_col+ncb2r,
                      nca2, ncb2);
    // P2 = S2 x B22
    strassen_imp(P, (const float* const *const) SA, (const float* const *const) temp,
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2r, nca2r, ncb2r);
                 
    // C12=P1(C12)+P2
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col+ncb2r,
                      C_f_row, C_f_col+ncb2r,
                      0, 0,
                      nra2r, ncb2);
    // C11=-P2
    sub_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2r, ncb2r);

    // S3 = A21 + A22
    reset(SA, nra2r, nca2r);
    sum_matrix_blocks(SA, (const float* const *const) SA, A,
                      0, 0,
                      0, 0,
                      A_f_row+nra2r, A_f_col,
                      nra2,nca2r);
    sum_matrix_blocks(SA, (const float* const *const) SA, A,
                      0, 0,
                      0, 0,
                      A_f_row + nra2r, A_f_col + nca2r,
                      nra2, nca2);

    // P3 = S3 x B11
    strassen_imp(P, (const float* const *const) SA, B,
                 0, 0,
                 0, 0,
                 B_f_row, B_f_col,
                 nra2r, nca2r, ncb2r);
      
    // C21=P3
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2r, C_f_col,
                      C_f_row+nra2r, C_f_col,
                      0, 0,
                      nra2, ncb2r);
    // C22=P1-P3
    sub_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2r, C_f_col+ncb2r,
                      C_f_row+nra2r, C_f_col+ncb2r,
                      0, 0,
                      nra2, ncb2); 
                                   
    // S4 = B21 - B11
    reset(SB, nca2r, ncb2r);
    sum_matrix_blocks(SB, (const float* const *const) SB, B,
                      0, 0,
                      0, 0,
                      B_f_row + nca2r, B_f_col,
                      nca2,ncb2r);
    sub_matrix_blocks(SB, (const float* const *const) SB, B,
                      0, 0,
                      0, 0,
                      B_f_row, B_f_col,
                      nca2r, ncb2r);
    //A22+padding
    deallocate_matrix(temp,nca2r);
    temp=allocate_matrix(nra2r,nca2r);
    sum_matrix_blocks(temp,(const float* const *const) temp,A,
                      0, 0,
                      0, 0,
                      A_f_row+nra2r, A_f_col+nca2r,
                      nra2, nca2);
    // P4 = A22 x S4
    strassen_imp(P, (const float* const *const) temp, (const float* const *const) SB,
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2r, nca2r, ncb2r);

    // C21=P3+P4
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2r, C_f_col,
                      C_f_row+nra2r, C_f_col,
                      0, 0,
                      nra2, ncb2r);
                    
    // C11=P4-P2
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2r, ncb2r);

    // S5 = A11 + A22
    reset(SA, nra2r, nca2r);
    sum_matrix_blocks(SA, (const float* const *const) SA, A,
                      0, 0,
                      0, 0,
                      A_f_row, A_f_col,
                      nra2r,nca2r);
    sum_matrix_blocks(SA, (const float* const *const) SA, A,
                      0, 0,
                      0, 0,
                      A_f_row + nra2r, A_f_col + nca2r,
                      nra2, nca2);

    // S6 = B11 + B22
    reset(SB, nca2r, ncb2r);
    sum_matrix_blocks(SB, (const float* const *const) SB, B,
                      0, 0,
                      0, 0,
                      B_f_row, B_f_col,
                      nca2r,ncb2r);
    sum_matrix_blocks(SB, (const float* const *const) SB, B,
                      0, 0,
                      0, 0,
                      B_f_row + nca2r, B_f_col + ncb2r,
                      nca2, ncb2);

    // P5 = S5 x S6
    strassen_imp(P, (const float* const *const) SA,
                 (const float* const *const) SB,
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2r, nca2r, ncb2r);

    // C11=P5+P4-P2
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2r, ncb2r);

    // C22=P5+P1-P3
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2r, C_f_col+ncb2r,
                      C_f_row+nra2r, C_f_col+ncb2r,
                      0, 0,
                      nra2, ncb2);

    // S7 = A12 - A22
    reset(SA, nra2r, nca2r);
    sum_matrix_blocks(SA, (const float* const *const) SA, A,
                      0, 0,
                      0, 0,
                      A_f_row, A_f_col + nca2r,
                      nra2r,nca2);
    sub_matrix_blocks(SA, (const float* const *const) SA, A,
                      0, 0,
                      0, 0,
                      A_f_row + nra2r, A_f_col + nca2r,
                      nra2, nca2);

    // S8 = B21 + B22
    reset(SB, nca2r, ncb2r);
    sum_matrix_blocks(SB, (const float* const *const) SB, B,
                      0, 0,
                      0, 0,
                      B_f_row + nca2r, B_f_col,
                      nca2,ncb2r);
    sum_matrix_blocks(SB, (const float* const *const) SB, B,
                      0, 0,
                      0, 0,
                      B_f_row + nca2r, B_f_col + ncb2r,
                      nca2, ncb2);

    // P6 = S7 x S8
    strassen_imp(P, (const float* const *const) SA,
                 (const float* const *const) SB,
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2r, nca2r, ncb2r);
    // C11=P6+P5+P4-P2
    sum_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nra2r, ncb2r);


    // S9 = A11 - A21
    reset(SA, nra2r, nca2r);
    sum_matrix_blocks(SA, (const float* const *const) SA, A,
                      0, 0,
                      0, 0,
                      A_f_row, A_f_col,
                      nra2r,nca2r);
    sub_matrix_blocks(SA, (const float* const *const) SA, A,
                      0, 0,
                      0, 0,
                      A_f_row + nra2r, A_f_col,
                      nra2, nca2r);

    // S10 = B11 + B12
    reset(SB, nca2r, ncb2r);
    sum_matrix_blocks(SB, (const float* const *const) SB, B,
                      0, 0,
                      0, 0,
                      B_f_row, B_f_col,
                      nca2r,ncb2r);         
    sum_matrix_blocks(SB, (const float* const *const) SB, B,
                      0, 0,
                      0, 0,
                      B_f_row, B_f_col + ncb2r,
                      nca2r, ncb2);

    // P7 = S9 x S10
    strassen_imp(P, (const float* const *const) SA,
                 (const float* const *const) SB,
                 0, 0,
                 0, 0,
                 0, 0,
                 nra2r, nca2r, ncb2r);
    // C22=-P7+P5+P1-P3
    sub_matrix_blocks(C, (const float* const *const) C, (const float* const *const) P,
                      C_f_row+nra2r, C_f_col+ncb2r,
                      C_f_row+nra2r, C_f_col+ncb2r,
                      0, 0,
                      nra2, ncb2);
                      
    deallocate_matrix(SA, nra2r);

    deallocate_matrix(SB, nca2r);

    deallocate_matrix(P, nra2r);

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

  strassen_imp(C, A, B,
               0, 0,
               0, 0,
               0, 0,
               nr_A, nc_A, nc_B);

}

