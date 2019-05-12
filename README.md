# matrix-multiplication
Basic matrix class to call cblas_dgemm from lapack. It can be used with openblas or Intel mkl optimization libs.
The program assumes the installation of openBLAS (https://github.com/xianyi/OpenBLAS). To link with Intel mkl or just cblas, remove #include <openblas/cblas.h> and set up the appropriate linking. 

The class is only a row major wrapper of a dynamic std::vector<double> or std::vector<float> using std::allocator.

Testing on core2 T7800 with 667Mhz bus speed showed no difference in performance between OpenBLAS and Intel mkl linking and its matrix multiplication operators are only 20% slower than those of the corresponding Armadillo's implementations for type double matrix entries but faster than Eigen's. Under the float type, this class' multiplication operators outperformed all the others.  
