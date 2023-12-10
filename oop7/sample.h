#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPainter>
#include "graph.h"

class Sample {
    Graph graph;

public:
    Sample(Graph);
    Sample();

    void paint(QPainter*,QRect);
    void paintLines(QPointF*, QPainter*, int i, int j, qreal);
    bool isConnected(int i, int j);

};

#endif
