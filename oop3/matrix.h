
#ifndef MATRIX_H
#define MATRIX_H


#include "number.h"

#include <iostream>

using namespace std;


class Matrix
{
public:
    Matrix();
    void enter(number x, int i, int j);
    void enterSize(int size);
    number activateDet();
    void transpose();
    int findRank();
    void reSize();
    int _size = 3;
    void updateTable(Matrix&);
    number getElement(int i, int j);
private:
    number matrix[10][10];
    number findDet(number matrix[10][10], int row);

};

#endif // MATRIX_H
