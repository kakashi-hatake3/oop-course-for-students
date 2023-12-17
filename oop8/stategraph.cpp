#include "stategraph.h"

StateGraph::StateGraph()
{
    this->selected = 0;
}

StateGraph::StateGraph(Graph g)
{
    this->selected = 0;
    this->graph = g;
}

void StateGraph::paint(QPainter* painter, QRect window){
    Sample::paint(painter, window);

    int count = this->graph.size();
    qreal pSize = 12;
    if (count > 33 && count <= 66) pSize = 10;
    else if (count > 66) pSize = 5;

    qreal centerW = 0.5 * window.width();
    qreal centerH = 0.5 * window.height() + 15;
    qreal circleR = (centerW > centerH ? centerH : centerW) - 2*pSize - 150;
    qreal gap = 2.0 * acos(-1.0)/count;

    QPointF t(centerW + circleR * sin(this->selected * gap),centerH - circleR * cos(this->selected * gap));
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::green));
    painter->drawEllipse(t,pSize,pSize);

    painter->drawText(QRectF(t.x()-pSize,t.y()-pSize, 2.0*pSize,2.0*pSize),
                      QString().setNum(this->selected+1), QTextOption(Qt::AlignCenter));
}

void StateGraph::onClickedEvent(bool direction){
    if (direction) this->selected++;
    else this->selected = --this->selected + this->graph.size();
    this->selected = this->selected % this->graph.size();
}
