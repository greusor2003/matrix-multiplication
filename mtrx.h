#include <iostream>
#include <cblas-openblas.h> // openblas interface of cblas
#include <vector>
#include <cassert>
#include <utility>

template<class T>
using vecT = std::vector<T>;

template<class T>
struct Mtrx;

template<class T>
void mult(Mtrx<T>&, Mtrx<T>&, Mtrx<T>&); 
//wrapper for cblas_dgemm etc

template<class T>
Mtrx<T> operator * (Mtrx<T>&, Mtrx<T>&);
//friend operator of Mtrx<T>

template<class T>
struct Mtrx
{
    size_t nrow;
    size_t ncol;
    Mtrx(): nrow(0), ncol(0), data(0){};
    explicit Mtrx(size_t M, size_t N): nrow(M), ncol(N), data(vecT<T>(M*N)){} 
    Mtrx(const Mtrx<T>& A): nrow(A.nrow), ncol(A.ncol){ data.assign(A.data.begin(), A.data.end());} 
    Mtrx(Mtrx<T>&& A) noexcept : nrow(std::exchange(A.nrow, 0)), ncol(std::exchange(A.ncol, 0)), data(std::move(A.data)){}
    
    T& operator()(size_t, size_t); 
    T operator()(size_t, size_t) const;
    Mtrx<T>& operator = (const Mtrx<T>&);
    Mtrx<T>& operator = (Mtrx<T>&&);
    Mtrx<T>& operator *= (Mtrx<T>&);
    
    friend void mult<>(Mtrx&, Mtrx&, Mtrx&);
    friend Mtrx operator * <>(Mtrx&, Mtrx&); 
    
    T* get_data() {return &*data.begin();} // for cblas_dgemm binding
    
    private:
    vecT<T> data;
};

template<class T>
Mtrx<T>& Mtrx<T>::operator = (const Mtrx<T>& A)
{
    ncol = A.ncol;
    nrow = A.nrow;
    data.assign(A.data.begin(), A.data.end());
    
    return *this;
}

template<class T>
Mtrx<T>& Mtrx<T>::operator = (Mtrx<T>&& A)
{
    if (this != &A)
    {        
	    *this = A;
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
    ncol = B.ncol;
    data = std::move(temp.data);
    return *this;   
}

template<class T>
Mtrx<T> operator * (Mtrx<T>& A, Mtrx<T>& B)
{
    assert(A.ncol == B.nrow);
    auto temp = Mtrx<T>(A.nrow, B.ncol);
    mult<T>(A, B, temp);
    return temp;
}

template <class T>
T& Mtrx<T>::operator()(size_t i, size_t j) 
{ 
    assert(ncol*i+j < nrow*ncol);
    return data[ncol*i + j];
}

template <class T>
T Mtrx<T>::operator()(size_t i, size_t j) const
{ 
    assert(ncol*i+j < nrow*ncol);
    return data[ncol*i + j];
}



