#ifndef MATRIX_H
#define MATRIX_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include <iostream>


template <class number>
class Matrix
{
private:
    number** matrix;

    int height;
    int width;

    Matrix minor(int row, int column);

public:
    Matrix(int height, int width);

    void print();
    void transpose();
    void fill();
    void wipe();
    void gauss();
    void copy(Matrix* mat);

    void applyChanges(int size, QString values);
    QString valuesToQString();

    int rank();
    void insert(int i, int j, number val);
    number retrieve(int i, int j);

    void setSize(int height, int width);
    void setValues();
    int getHeight();
    int getWidth();
};

template <class number>
number QStringToNumber(QString val);

template <class number>
Matrix<number>::Matrix(int height, int width)
{
    this->height = height;
    this->width = width;

    matrix = new number* [width];
    for (int i = 0; i < width; ++i)
        matrix[i] = new number [height];

    for (int i = 0; i < this->width; ++i) {
        for (int j = 0; j < this->height; ++j) {
            matrix[i][j] = 0;
        }
    }
}

template <class number>
number Matrix<number>::retrieve(int i, int j) {
    return matrix[i][j];
}

template <class number>
void Matrix<number>::insert(int i, int j, number val) {
    matrix[i][j] = val;
}

template <class number>
void Matrix<number>::wipe()
{
    for (int i = 0; i < this->height; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

template <class number>
void Matrix<number>::setSize(int height, int width)
{
    wipe();
    this->height = height;
    this->width = width;

    matrix = new number* [width];
    for (int i = 0; i < width; ++i)
        matrix[i] = new number [height];

    for (int i = 0; i < this->width; ++i) {
        for (int j = 0; j < this->height; ++j) {
            matrix[i][j] = 0;
        }
    }
}

template <class number>
int Matrix<number>::getHeight()
{
    return this->height;
}

template <class number>
int Matrix<number>::getWidth()
{
    return this->width;
}

template <class number>
void Matrix<number>::setValues()
{

    std::cout << "Please, enter the matrix values (from left to right)\n";
    for (int i = 0; i < this->width; ++i)
    {
        for (int j = 0; j < this->height; ++j)
        {
            std::cin >> this->matrix[i][j];
        }

    }
}


template <class number>
void Matrix<number>::copy(Matrix* mat) {
    if (!(this->width == mat->width && this->height == mat->height)) {
        qInfo() << "Matrix can't be copied";
        return;
    }

    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            this->matrix[i][j] = mat->matrix[i][j];
        }
    }
}


template <class number>
void Matrix<number>::transpose()
{
    Matrix *tmp = new Matrix(this->width, this->height);
    tmp->copy(this);

    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            this->matrix[i][j] = tmp->matrix[j][i];
        }
    }

    delete tmp;
}

template <class number>
void Matrix<number>::gauss() {
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; i < this->height; ++i) {
        int row_max = i;

        for (j = i + 1; j < this->height; ++j) {
            if (matrix[j][i].abs() > matrix[row_max][i].abs()) {
                row_max = j;
            }
        }

        for (k = 0; k < this->width; ++k) {
            number tmp = this->matrix[i][k];
            this->matrix[i][k] = this->matrix[row_max][k];
            this->matrix[row_max][k] = tmp;
        }

        for (j = i + 1; j < this->height; ++j) {
            number q = - matrix[j][i] / matrix[i][i];
            for (k = this->width - 1; k >= i; -- k)
                this->matrix[j][k] = this->matrix[j][k] + q * this->matrix[i][k];
        }
    }
}

template <class number>
int Matrix<number>::rank() {
    int rnk = 0;

    Matrix *tmp = new Matrix{this->height, this->width};
    tmp->copy(this);
    tmp->gauss();

    for (int i = 0; i < tmp->height; ++i) {
        number row_sum = 0;

        for (int j = 0; j < tmp->width; ++j) {
            row_sum = row_sum + tmp->matrix[i][j];
        }

        if (row_sum != 0) {
            rnk += 1;
        }
    }

    tmp->wipe();

    return rnk;
}

template <class number>
void Matrix<number>::applyChanges(int size, QString values) {
    QStringList values_arr;
    number val;

    if (size * size != this->width * this->height) {
        setSize(size, size);
    }

    values_arr = values.split(',');

    for (int ind = 0; ind < values_arr.size(); ++ind) {
        val = values_arr[ind];
        insert(ind / this->width, ind % this->width, val);
    }
}

template <class number>
QString Matrix<number>::valuesToQString() {
    QString values;

    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            values.append(matrix[i][j].toQString());
            values.append(',');
        }
    }

    values.chop(1);
    return values;
}

#endif
