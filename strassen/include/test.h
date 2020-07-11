#ifndef __TEST__


double test(void (*f)(float **,
	                  float const *const *const,
	                  float const *const *const,
	                  size_t, size_t, size_t),
	        float **C, float** A, float **B, size_t nr_A, size_t nc_A, size_t nr_B);

#endif // __TEST__
