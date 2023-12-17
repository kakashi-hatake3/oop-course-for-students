#ifndef STATEGRAPH_H
#define STATEGRAPH_H

#include "sample.h"
#include <math.h>

class StateGraph : public Sample
{
    int selected;
public:
    StateGraph(Graph g);
    void paint(QPainter*,QRect);
    void onClickedEvent(bool);
    StateGraph();

};
#endif // STATEGRAPH_H
