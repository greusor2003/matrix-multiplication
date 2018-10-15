//#pragma once
#include "MtrxOpenBlas.h"
#include <chrono>
#include <cstdlib>
#include <ctime>


int main()
{
	
	size_t m = 1, k = 1, n = 1;
	while (m > 0)
	{
		cout << endl;
		cout << "Insert the integers m > 0, k > 0, n > 0  to multiply the matrices A(m,k) and B(k, n) \n";
		cout << "or insert 0 to quit. \n";
		cout << "m = "; cin >> m; cout << endl;
		if (!(m > 0)) break;
		cout << "k = "; cin >> k; cout << endl;
		cout << "n = "; cin >> n; cout << endl;

		// initialize marices
		vector<double> A(m*k, 0.0);
		vector<double> B(k*n, 0.0);
		vector<double> C(m*n, 0.0);

		// load matrices
		srand((int)time(0));
		size_t i = 0;

		for (i = 0; i < (m*k); i++) {
			//A[i] = ((double)rand() / 100.0 + 1.0);
			A[i] = (double)rand() / RAND_MAX + 1.0;
		}

		for (i = 0; i < (k*n); i++) {
			B[i] = (double)rand() / RAND_MAX  + 1.0;
		}

		for (i = 0; i < (m*n); i++) {
			C[i] = 0.0;
		}

		// timing
		auto start = std::chrono::system_clock::now();

		//cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
					//m, n, k, alpha, A, k, B, n, beta, C, n);

		matrix_mult(A.begin(), m, k, B.begin(), k, n, C.begin());

		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

        // prints out the first 8 columns of the first 8 rows
		for (int i = 0; i < std::min((int)m, 8); i++) {
			for (int j = 0; j < std::min((int)n, 8); j++) {
				cout << C[j + i * k] << " ";
			}
			cout << endl;
		}
	}
	
	return 0;
}
