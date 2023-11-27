
#ifndef MATRIX_H
#define MATRIX_H



#include <numeric>
#include <iostream>
#include <vector>

using namespace std;

template <class number>
class Matrix
{
public:
    Matrix();
    ~Matrix();
    void enter(number x, int i, int j);
    void enterSize(int size);

    void transpose();
    int findRank();
    void reSize(int n, int m);
   // int _size = 3;
    int  m = 3, n = 3;
    number getEl(int i, int j);
    void wipe(number** matr);
    number** matrixCpy();
private:
    number** matrix;
};
template <class number>
Matrix<number>::Matrix()
{   int res = 0;
    matrix = new number* [n];
    for (int i = 0; i < n; ++i)
        matrix[i] = new number [m];


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = res++;
        }
    }

}
template <class number>
void Matrix<number>::enter(number x, int i, int j)

{
    matrix[i][j] = x;

}

template <class number>
void Matrix<number>::reSize(int n, int m) {
    wipe(matrix);
    this->n = n;
    this->m = m;
    matrix = new number* [n];
    for (int i = 0; i < n; ++i)
        matrix[i] = new number [m];


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = 0;
        }
    }

}
template <class number>
void Matrix<number>::transpose()
{
    Matrix tmp = Matrix();
    tmp.reSize(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            tmp.matrix[i][j] = matrix[i][j];
        }
    }

    number t;
    reSize(m, n);
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            matrix[i][j] = tmp.getEl(j, i);
        }
    }
}
template <class number>
number** Matrix<number>::matrixCpy()
{
    return matrix;
}

template <class number>
int Matrix<number>::findRank()
{

    const double EPS = 1E-9;
    int rank = max(m, n);
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
template <class number>
number Matrix<number>::getEl(int i, int j) {
    return matrix[i][j];
}

template <class number>
void Matrix<number>::wipe(number** matr)
{
    for (int i = 0; i < n; ++i) {
        delete[] matr[i];
    }

    delete[] matr;
}
template <class number>
Matrix<number>::~Matrix()
{

}

#endif // MATRIX_H
