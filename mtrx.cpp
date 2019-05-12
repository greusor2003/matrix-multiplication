#include "mtrx.h"
#include <random> 
#include <iomanip>
 
template <class T>
void rnd_load(Mtrx<T>& M)
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<T> dis(0.0, 1.0);
  for (size_t i = 0; i < M.nrow; i++)
      for (size_t j = 0; j < M.ncol; j++)
          M(i,j) = dis(gen);  
}

template <class T>
void rnd_load_int(Mtrx<float>& M)
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<T> dis(0, 5);
  for (size_t i = 0; i < M.nrow; i++)
      for (size_t j = 0; j < M.ncol; j++)
          M(i,j) = (float)dis(gen);  
}

template <class T>
void printM(const Mtrx<T>& M, const size_t I, const size_t J )
{
    assert(M.nrow >= I and M.ncol >= J);
    for (size_t i = 0; i < I; i++)
    {
        for (size_t j = 0; j < J; j++)
            std::cout << std::fixed << std::setprecision(2)<< M(i,j) <<" ";
        std::cout << "\n";
    }
}

template <>
void mult(Mtrx<double>& A, Mtrx<double>& B, Mtrx<double>& C)
{
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, A.nrow, B.ncol, B.nrow, 1.0, 
                A.get_data(), A.ncol, B.get_data(), B.ncol, 0.0, C.get_data(), B.ncol);
}

template <>
void mult(Mtrx<float>& A, Mtrx<float>& B, Mtrx<float>& C)
{
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, A.nrow, B.ncol, B.nrow, 1.0, 
                A.get_data(), A.ncol, B.get_data(), B.ncol, 0.0, C.get_data(), B.ncol);
}



