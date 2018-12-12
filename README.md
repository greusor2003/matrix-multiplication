# matrix-multiplication
std::vector wrapper to call cblas_dgemm from lapack. It can be used with openblas or Intel mkl optimization libs.
the program assumes the installation of openBLAS (https://github.com/xianyi/OpenBLAS). To link with Intel mkl or just cblas, remove #include <openblas/cblas.h> and set up the appropriate linking. 

Testing on core2 T7800 with 667Mhz bus speed showed no difference in performance between OpenBLAS and Intel mkl linking. Moreover, Python 3.6 with numpy 1.15.2 (OpenBlas) returned the same results.  
