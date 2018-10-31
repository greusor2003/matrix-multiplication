#pragma once
#include <iostream>
#include <cassert>
#include <algorithm>
#include <chrono>
#include <vector>
#include <openblas/cblas.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

typedef vector<double>::iterator vectype;

void matrix_mult(vectype, size_t, size_t, vectype, size_t, size_t, vectype);
