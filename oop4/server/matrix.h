
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
    number activateDet();
    void transpose();
    int findRank();
    void reSize(int size_);
    int _size = 3;
    number getEl(int i, int j);
private:
    number findDet(number** matrix, int row);
    number** matrix;
    void wipe(number** matr);

};

#endif // MATRIX_H
