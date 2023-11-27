
#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "matrix.h"



class Interface : public QWidget

{
    Q_OBJECT
    QTableWidget *table;
    Matrix matrix;
    QPushButton* transpose;
    QPushButton* rank;
    QPushButton* det;
    QLabel* result_det;
    QLabel* result_rank;
    QLineEdit* size;
    QLabel* size_label;

public slots:
    void transposition();
    void changed();
    void rankOfMatrix();
    void determination();
    void resize();

public:
    QTableWidget* getTable(){
        return table;
    }
    Interface(QWidget *parent = nullptr);
    ~Interface();
};

#endif // INTERFACE_H
