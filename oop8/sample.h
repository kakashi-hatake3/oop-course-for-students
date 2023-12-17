#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPainter>
#include "graph.h"

class Sample {
public:
    Sample(Graph);
    Sample();

    Graph graph;

    void paint(QPainter*,QRect);
    void paintLines(QPointF*, QPainter*, int i, int j, qreal);
    bool isConnected(int i, int j);

};

#endif
