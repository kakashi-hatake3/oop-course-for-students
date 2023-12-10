#ifndef GRAPH_H
#define GRAPH_H
#include "matrix.h"
#include <QFile>
#include <QTextStream>


class Graph
{
private:
    Matrix<int>* adj;

    int graph_size = 4;

public:
    Graph();
    void set(QString);
    int size();
    int retrieve(int, int);
};

#endif
