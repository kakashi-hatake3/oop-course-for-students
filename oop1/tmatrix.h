
#ifndef TMATRIX_H
#define TMATRIX_H
#include "number.h"
#include <iostream>
using namespace std;



class TMatrix
{
    number a, b, c, d;
public:
    TMatrix(number, number, number, number);
    friend ostream& operator<< (ostream&, TMatrix&);
};

#endif // TMATRIX_H
