#include "mtrx.cpp"
#include <chrono>

using std::cin;
using std::cout;
using std::endl;

using tp = double; // choose between double and float by commenting and uncommenting correspondingly
//using tp = float;

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
    
    	Mtrx<tp> A(m,k);
    	Mtrx<tp> B(k,n);
    	Mtrx<tp> C;
        
	rnd_load<tp>(A); // loads A with doubles or floats
    	rnd_load<tp>(B);

		//rnd_load_int<unsigned short int>(A); //loads A with unsigned int cast to float
		//rnd_load_int<unsigned short int>(B);
	
		printM<tp>(A, 5, 8); //prints out the top 5 rows and the first 8 columns from the left 

		cout << "\n";
		
		printM<tp>(B, 8, 4);
	
    	auto start = std::chrono::system_clock::now(); //start timing
		A *= B;  
        	//C = A*B; 
        
    	auto end = std::chrono::system_clock::now(); //end of timing
    	std::chrono::duration<double> elapsed_seconds = end - start;
    	std::cout << "\n Elapsed time: " << elapsed_seconds.count() << "s\n\n";

		printM<tp>(A, 5, 4);
    	//printM<tp>(C, 5, 4);
		
    }
    return 0;
}
