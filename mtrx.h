#include <iostream>
#include <cblas-openblas.h>
#include <cassert>

template<class T>
struct Mtrx
{
    const size_t nrow;
    const size_t ncol;
    Mtrx():nrow(0), ncol(0), data(nullptr) {}
    Mtrx(size_t M, size_t N): nrow(M), ncol(N), /*data(M*N)*/data(new T[M*N]){} 
    ~Mtrx() { if(data != nullptr) delete [] data; }
    T& operator()(size_t, size_t); 
    T operator()(size_t, size_t) const;
    T* get_data() {return data;}
    private:
    T* data;
};

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
