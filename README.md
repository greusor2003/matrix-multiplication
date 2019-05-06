# matrix-multiplication
Basic matrix class to call cblas_dgemm from lapack. It can be used with openblas or Intel mkl optimization libs.
The program assumes the installation of openBLAS (https://github.com/xianyi/OpenBLAS). To link with Intel mkl or just cblas, remove #include <openblas/cblas.h> and set up the appropriate linking. 

Testing on core2 T7800 with 667Mhz bus speed showed no difference in performance between OpenBLAS and Intel mkl linking. 
