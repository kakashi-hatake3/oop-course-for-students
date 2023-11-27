
#include "squarematrix.h"
#include <cmath>

squareMatrix::squareMatrix()
{

}


number squareMatrix::activateDet() {
    number res = findDet(matrix,_size );
    return res;
}

number squareMatrix::findDet(number** matrix, int row) {
    number det = 0;
    number** Minor;
    Minor = new number* [_size];
    for (int i = 0; i < _size; ++i)
        Minor[i] = new number[_size];


    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            Minor[i][j] = 0;
        }
    }
    number p = 1;
    if (row == 1) {
        wipe(Minor);
        return matrix[0][0];
    }
    else if (row == 2){
        wipe(Minor);
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));}
    else {
        for (int i = 0; i < row; i++) {
            int ki = 0;
            for (int j = 1; j < row; j++) {
                int kj = 0;
                for (int m= 0; m < row; m++) {
                    if (m == i)
                        continue;
                    Minor[ki][kj] = matrix[j][m];
                    kj++;
                }
                ki++;
            }
            p = pow(-1, i);

            det = det + (p * matrix[0][i] * findDet(Minor, row - 1));
        }
        wipe(Minor);
    }if(det.numerator != 0 && det.devider != 0) {
        int g = std::gcd(det.devider, det.numerator);
        det.numerator = det.numerator/g;
        det.devider = det.devider/g;
        return det;
    }


    return det;

}
