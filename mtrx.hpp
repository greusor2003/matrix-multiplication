#ifndef MTRX_HPP
#define MTRX_HPP

#include "mtrx.h"


template <class T>
Mtrx<T>::Mtrx(const Mtrx<T>& A)
  {
        Mtrx(A.nrow, A.ncol);
        for(size_t i=0; i< nrow*ncol; i++ )
            content[i] = A.content[i];
  }

template <class T>
Mtrx<T>::~Mtrx()
{
    delete [] content;
}

template <class T>
Mtrx<T>::Mtrx(Mtrx<T>&& A)
{
    nrow = A.nrow;
    ncol = A.ncol;
    content = A.content;
    A.content = nullptr;

}

template<class T>
Mtrx<T>& Mtrx<T>::operator = (const Mtrx<T>& A)
{
    if (this != &A)
    {
        delete [] content;
        nrow = A.nrow;
        ncol = A.ncol;
        content = new T[ncol*nrow];
        for(size_t i=0; i< nrow*ncol; i++ )
            content[i] = A.content[i];
        return *this;
    }
    else
        return *this;
}


template<class T>
Mtrx<T>& Mtrx<T>::operator = (Mtrx<T>&& A)
{
    if (this != &A)
    {
        delete [] content;
        ncol = A.ncol;
        nrow = A.nrow;
        content = A.content;
        A.content = nullptr;
        return *this;
    }
    return *this;
}


template<class T>
Mtrx<T>& Mtrx<T>::operator *= (Mtrx<T>& B)
{
    assert(ncol == B.nrow);    
    Mtrx<T> temp(nrow, B.ncol);
    mult<T>(*this, B, temp);
    *this = temp;
    return *this;
}

template<class T>
Mtrx<T> operator * (Mtrx<T>& A, Mtrx<T>& B)
{
    assert(A.ncol == B.nrow);
    Mtrx<T> temp(A.nrow, B.ncol);
    mult<T>(A, B, temp);
    return temp;
}

template <class T>
T& Mtrx<T>::operator()(size_t i, size_t j)
{
    assert(ncol*i+j < nrow*ncol);
    return content[ncol*i + j];
}

template <class T>
T Mtrx<T>::operator()(size_t i, size_t j) const
{
    assert(ncol*i+j < nrow*ncol);
    return content[ncol*i + j];
}

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
    std::cout<<"\n";
}

template <>
void mult(Mtrx<double>& A, Mtrx<double>& B, Mtrx<double>& C)
{

    auto Ar = static_cast<blasint>(A.nrow);
    auto Ac = static_cast<blasint>(A.ncol);
    auto Br = static_cast<blasint>(B.nrow);
    auto Bc = static_cast<blasint>(B.ncol);


    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, Ar, Bc, Br, 1.0,
                A.get_data(), Ac, B.get_data(), Bc, 0.0, C.get_data(), Bc);
}

template <>
void mult(Mtrx<float>& A, Mtrx<float>& B, Mtrx<float>& C)
{
    auto Ar = static_cast<blasint>(A.nrow);
    auto Ac = static_cast<blasint>(A.ncol);
    auto Br = static_cast<blasint>(B.nrow);
    auto Bc = static_cast<blasint>(B.ncol);
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, Ar, Bc, Br, 1.0,
                A.get_data(), Ac, B.get_data(), Bc, 0.0, C.get_data(), Bc);
}


#endif // MTRX_HPP
