
#include "matrix.h"
#include <cmath>
#include <QDebug>

Matrix::Matrix()
{   int res = 0;
    matrix = new number* [_size];
    for (int i = 0; i < _size; ++i)
        matrix[i] = new number [_size];


    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            matrix[i][j] = res++;
        }
    }

}



void Matrix::enter(number x, int i, int j)

{
    matrix[i][j] = x;

}
void Matrix::reSize(int size_) {
    wipe(matrix);
    _size = size_;
    matrix = new number* [_size];
    for (int i = 0; i < _size; ++i)
        matrix[i] = new number [_size];


    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            matrix[i][j] = 0;
        }
    }

}
void Matrix::enterSize(int size_) {
    _size = size_;
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
    const double EPS = 1E-9;

    int rank = _size;
    int m = rank;
    int n = rank;
    vector<char> line_used (n);
    for (int i=0; i<m; ++i) {
        int j;
        for (j=0; j<n; ++j)
            if (!line_used[j] && abs(matrix[j][i].numerator) > EPS)
                break;
        if (j == n)
            --rank;
        else {
            line_used[j] = true;
            for (int p=i+1; p<m; ++p)
                matrix[j][p] = matrix[j][p] /  matrix[j][i];
            for (int k=0; k<n; ++k)
                if (k != j && abs (matrix[k][i].numerator) > EPS)
                    for (int p=i+1; p<m; ++p)
                        matrix[k][p] = matrix[k][p] - matrix[j][p] * matrix[k][i];
        }
    }

    return rank;

}
number Matrix::getEl(int i, int j) {
    return matrix[i][j];
}

void Matrix::wipe(number** matr)
{
    for (int i = 0; i < _size; ++i) {
        delete[] matr[i];
    }

    delete[] matr;
}

Matrix::~Matrix()
{

}




