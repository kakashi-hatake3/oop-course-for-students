
#include "matrix.h"
#include <cmath>
#include "interface.h"

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
    Rational p = 1;
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
    const double EPS = 1E-9;

    int rank = _size;
    int m = rank;
    int n = rank;
    vector<char> line_used (n);
    for (int i=0; i<m; ++i) {
        int j;
        for (j=0; j<n; ++j)
            if (!line_used[j] && abs(matrix[j][i].ch) > EPS)
                break;
        if (j == n)
            --rank;
        else {
            line_used[j] = true;
            for (int p=i+1; p<m; ++p)
                matrix[j][p] = matrix[j][p] /  matrix[j][i];
            for (int k=0; k<n; ++k)
                if (k != j && abs (matrix[k][i].ch) > EPS)
                    for (int p=i+1; p<m; ++p)
                        matrix[k][p] = matrix[k][p] - matrix[j][p] * matrix[k][i];
        }
    }
    return rank;

}
number Matrix::getElement(int i, int j){
    return matrix[i][j];
}

//void Matrix::updateTable(Matrix& m){
//    Interface inter;
//    QTableWidget* a = inter.getTable();
//    a->setColumnCount(m._size);
//    a->setRowCount(m._size);
//    for(int i = 0; i < m._size; i++) {
//        for(int j = 0; j < m._size; j++) {
//            QTableWidgetItem* cell = new QTableWidgetItem(QString::number(m.matrix[i][j].ch) + "/" + QString::number(m.matrix[i][j].zn));
//            a->setItem(i, j, cell);
//        }
//    }
//}

//ostream& operator<<(ostream& os, Matrix& m){

//    for(int i = 0; i < m._size; i++) {
//        for(int j = 0; j < m._size; j++) {

//            os << m.matrix[i][j] << " ";
//        }
//        os<<"\n";
//    }
//    return os;
//}

