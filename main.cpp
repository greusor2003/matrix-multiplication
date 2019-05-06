#include "mtrx.cpp"
#include <chrono>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    size_t m = 1; size_t k = 1; size_t n = 1;
    while (m > 0)
    {
	cout << endl;
	cout << "Insert the integers m > 0, k > 0, n > 0  to multiply the matrices A(m,k) and B(k, n) \n";
	cout << "or insert 0 to quit. \n";
	cout << "m = "; cin >> m; cout << endl;
	if (!(m > 0)) break;
		cout << "k = "; cin >> k; cout << endl;
		cout << "n = "; cin >> n; cout << endl;
    
    	Mtrx<double> A(m,k);
    	Mtrx<double> B(k,n);
    	Mtrx<double> C(m,n);
    

    	rnd_load(A);
    	rnd_load(B);
    	double alpha = 1.0; 
	double beta = 0.0;  
    
    	auto start = std::chrono::system_clock::now(); //start timing
	// http://www.netlib.org/lapack/explore-html/d7/d2b/dgemm_8f.html
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, A.get_data(), k, B.get_data(), n, beta, C.get_data(), n);
    	auto end = std::chrono::system_clock::now();
    	std::chrono::duration<double> elapsed_seconds = end - start;
    	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    
    	printM(C, 8, 4);
    }
    return 0;
}
