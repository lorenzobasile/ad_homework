#ifndef __STRASSEN__

void strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B, size_t nr_A, size_t nc_A, size_t nc_B);

void strassen_improved(float **C, float const *const *const A,
                                    float const *const *const B, size_t nr_A, size_t nc_A, size_t nc_B);
#endif //__STRASSEN__
