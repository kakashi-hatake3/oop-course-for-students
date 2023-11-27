
#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H
#include "matrix.h"



class squareMatrix: public Matrix
{
public:
    squareMatrix();
    number activateDet();
    number findDet(number** matrix, int row);


};

#endif // SQUAREMATRIX_H
