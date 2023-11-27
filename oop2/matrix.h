
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
    friend ostream& operator<<(ostream&, Matrix&);
    number activateDet();
    void transpose();
    int findRank();
    void reSize();
    int _size = 3;
private:

     number findDet(number matrix[10][10], int row);
     number matrix[10][10];

};

#endif // MATRIX_H
