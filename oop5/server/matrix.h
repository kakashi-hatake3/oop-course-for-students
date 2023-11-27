
#ifndef MATRIX_H
#define MATRIX_H


#include "number.h"
#include <numeric>
#include <iostream>

using namespace std;


class Matrix
{
public:
    Matrix();
    ~Matrix();
    void enter(number x, int i, int j);
    void enterSize(int size);
    void transpose();
    int findRank();
    void reSize(int size_);
    int _size = 3;
    number getEl(int i, int j);
    void wipe(number** matr);
    number** matrix;
};

#endif // MATRIX_H
