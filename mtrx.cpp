#include "mtrx.h"
#include <random>

void rnd_load(Mtrx<double>& M)
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(0.0, 1.0);
  for (size_t i = 0; i < M.nrow; i++)
      for (size_t j = 0; j < M.ncol; j++)
          M(i,j) = dis(gen);  
}

void printM(const Mtrx<double>& M, const size_t I, const size_t J )
{
    for (size_t i = 0; i < I; i++)
    {
        for (size_t j = 0; j < J; j++)
            std::cout << M(i,j) <<" ";
        std::cout << "\n";
    }
}
