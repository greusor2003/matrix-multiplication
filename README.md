# matrix-multiplication
Basic matrix class to call cblas_dgemm of lapack. It can be used with openBLAS or Intel mkl optimization libs.
The current program assumes the installation of openBLAS (https://github.com/xianyi/OpenBLAS). To link with Intel mkl or just cblas, remove #include <openblas/cblas.h> and set up the appropriate linking. 

Testing on a core2 T7800, 667Mhz bus speed machine at the same CPU temperature showed no difference in performance between OpenBLAS and Intel mkl linking. Its matrix multiplication operators are speed comparable with those of the corresponding Armadillo's or numpy implementations for matrices with entries of type double, but faster than Eigen's. Under the float type, this class' multiplication operators outperformed all the others.  
