
#include "matrix.h"
#include <cmath>

Matrix::Matrix()
{   int res = 0;
    for(int i = 0; i < _size; i++) {
        for(int j = 0; j < _size; j++) {
            matrix[i][j] = res;
            res += 1;
        }
    }


}
void Matrix::enter(number x, int i, int j)

{
    matrix[i][j] = x;

}
void Matrix::reSize() {
    int res = 0;
    for(int i = 0; i < _size; i++) {
        for(int j = 0; j < _size; j++) {
            matrix[i][j] = res;
            res += 1;
        }
    }

}
void Matrix::enterSize(int size_) {
    _size = size_;
}
number Matrix::activateDet() {
    number res = findDet(matrix,_size );
    return res;
}
number Matrix::findDet(number matrix[10][10], int row) {
    number det = 0;
    number Minor[10][10];
    complex p = 1;
    if (row == 1) {
        return matrix[0][0];
    }
    else if (row == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
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
    }
    return det;

}
void Matrix::transpose()
{
    number t;
    for(int i = 0; i < _size; ++i)
    {
        for(int j = i; j < _size; ++j)
        {
            t = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = t;
        }
    }
}

int Matrix::findRank()
{
    number matr[10][10];
    copy(&matrix[0][0], &matrix[0][0] + 3 * 3, &matr[0][0]);
    const int ROWS = _size;
    const int COLS = _size;
    int rank = COLS;

        for (int row = 0; row < rank; row++) {
            if (matr[row][row] != 0) {
                for (int col = 0; col < ROWS; col++) {
                    if (col != row) {
                        complex mult = matr[col][row] / matr[row][row];
                        for (int i = 0; i < rank; i++)
                            matr[col][i] = matr[col][row] - mult * matr[row][i];
                    }
                }
            } else {
                bool reduce = true;
                for (int i = row + 1; i < ROWS; i++) {
                    if (matr[i][row] != 0) {
                        swap(matr[row], matr[i]);
                        reduce = false;
                        break;
                    }
                }
                if (reduce) {
                    rank--;
                    for (int i = 0; i < ROWS; i++)
                        matr[i][row] = matr[i][rank];
                }
                row--;
            }
        }
        return rank;


}


ostream& operator<<(ostream& os, Matrix& m)
{

    for(int i = 0; i < m._size; i++) {
        for(int j = 0; j < m._size; j++) {

            os << m.matrix[i][j] << " ";
        }
        os<<"\n";
    }
    return os;
}
