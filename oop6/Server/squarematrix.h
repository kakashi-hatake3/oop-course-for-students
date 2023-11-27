
#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "matrix.h"
#include "rational.h"
#include <cmath>

template <class number>
class SquareMatrix : public Matrix<number>
{
public:
    SquareMatrix();
     number activateDet();
private:
     number findDet(number** matrix, int row);
};

template <class number>
SquareMatrix<number>::SquareMatrix():Matrix<number>()
{
     this->m = 3;
     this->n =3;
}
template <class number>
number SquareMatrix<number>::activateDet() {

     number res = findDet(this->matrixCpy(), this->m);
     return res;
}
template <class number>
number SquareMatrix<number>::findDet(number** matrix, int row) {
     number det = 0;
     number** Minor;
     int m = this->m;
     Minor = new number* [m];
     for (int i = 0; i < m; ++i)
         Minor[i] = new number[m];


     for (int i = 0; i < m; ++i) {
         for (int j = 0; j < m; ++j) {
             Minor[i][j] = 0;
         }
     }
     number p = 1;
     if (row == 1) {
         this->wipe(Minor);
         return matrix[0][0];
     }
     else if (row == 2){
         this->wipe(Minor);
         return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));}
     else {
         for (int i = 0; i < row; i++) {
             int ki = 0;
             for (int j = 1; j < row; j++) {
                 int kj = 0;
                 for (int m= 0; m < row; m++) {                    if (m == i)
                         continue;
                     Minor[ki][kj] = matrix[j][m];
                     kj++;
                 }
                 ki++;           }
             p = pow(-1, i);

             det = det + (p * matrix[0][i] * findDet(Minor, row - 1));
         }
         this->wipe(Minor);
     }



     return det;

}

#endif // SQUAREMATRIX_H
