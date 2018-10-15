#include "MtrxOpenBlas.h"

// matrices A and B are loaded as the vectors formed by chaining their rows from top to bottom
// changes AB into the matrix product of A and B
// A_height = A's rows number; A_width = B's columns number
void matrix_mult(vectype A, size_t A_height, size_t A_width, 
	vectype B, size_t B_height, size_t B_width, 
	vectype AB)
{

	
	assert(A_width == B_height); // algebraic condition for matrix multiplication
	auto m = static_cast<int>(A_height);
	auto n = static_cast<int>(B_width);
	auto k = static_cast<int>(A_width);
	k = static_cast<int>(B_height);
	double alpha = 1.0; 
	double beta = 0.0;  

	// http://www.netlib.org/lapack/explore-html/d7/d2b/dgemm_8f.html
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, &*A, k, &*B, n, beta, &*AB, n);

}
