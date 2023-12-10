#include "sample.h"
#include <math.h>
#include <QDebug>

Sample::Sample(Graph graph) {
    this->graph = graph;
}

Sample::Sample(){

};

void Sample::paint(QPainter* painter, QRect window) {

    int count = this->graph.size();

    qreal pSize = 12;
    if (count > 33 && count <= 66) pSize = 10;
    else if (count > 66) pSize = 5;

    qreal centerW = 0.5 * window.width();
    qreal centerH = 0.5 * window.height() + 15;
    qreal circleR = (centerW > centerH ? centerH : centerW) - 2*pSize - 150;
    qreal gap = 2.0 * acos(-1.0)/count;

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(pSize);
    painter->setFont(font);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    pen.setBrush(QBrush(Qt::blue));
    painter->setPen(pen);

    QPointF *t = new QPointF[count];
    qreal x, y;

    for (int i = 0; i < count; i++) {
        x = centerW + circleR*sin(i*gap);
        y = centerH - circleR*cos(i*gap);
        t[i] = QPointF(x, y);
    }

    for (int i = 0; i < count; i ++)
        for (int j = 0; j < count; j++) {
            if (this->graph.retrieve(i, j) != 0)
                paintLines(t, painter, i, j, pSize);
        }

    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::yellow));

    for (int i=0; i<count; i++) {
        painter->setPen(QPen(Qt::darkGray));
        painter->drawEllipse(t[i], pSize, pSize);
        painter->setPen(QPen(Qt::blue));
        painter->drawText(QRectF(t[i].x()-pSize,t[i].y()-pSize, 2.0*pSize,2.0*pSize),
                          QString().setNum(i+1), QTextOption(Qt::AlignCenter));
    }

    delete [] t;
}

void Sample::paintLines(QPointF *t, QPainter *p, int i, int j, qreal radius){
    qreal angle = 2.0 * acos(-1.0)/this->graph.size();
    qreal circleX, circleY;
    if (i==j) {
        p->setBrush(QBrush());
        circleX = t[i].x() + radius*sin(i*angle);
        circleY = t[i].y() - radius*cos(i*angle);
        p->drawEllipse(QPointF(circleX,circleY), radius/2, radius/2);
        p->setBrush(QBrush(Qt::yellow));
    } else {
        p->drawLine(t[i], t[j]);

        qreal k = (t[j].y() - t[i].y()) / (t[j].x() - t[i].x());

        if ((t[j].x() < t[i].x()) && t[j].y() > t[i].y()){
            circleX = t[j].x() + radius*cos((atan(k)));
            circleY = t[j].y() + radius*sin((atan(k)));

        } else if ((t[j].x() > t[i].x()) && t[j].y() > t[i].y()){
            circleX = t[j].x() - radius*cos(atan(k));
            circleY = t[j].y() - radius*sin(atan(k));

        } else if ((t[j].x() < t[i].x()) && t[j].y() < t[i].y()){
            circleX = t[j].x() + radius*cos(atan(k));
            circleY = t[j].y() + radius*sin(atan(k));

        } else if ((t[j].x() > t[i].x()) && t[j].y() < t[i].y()) {
            circleX = t[j].x() - radius*cos(atan(k));
            circleY = t[j].y() - radius*sin(atan(k));


        } else if ((t[j].x() == t[i].x()) && t[j].y() < t[i].y()) {
            circleX = t[j].x() - radius*cos(atan(k)) * 0;
            circleY = t[j].y() - radius*sin(atan(k));

        } else if ((t[j].x() == t[i].x()) && t[j].y() > t[i].y()) {
            circleX = t[j].x() - radius*cos(atan(k)) * 0;
            circleY = t[j].y() - radius*sin(atan(k));

        } else if ((t[j].x() > t[i].x()) && t[j].y() == t[i].y()) {
            circleX = t[j].x() - radius*cos(atan(k));
            circleY = t[j].y() - radius*sin(atan(k)) * 0;

        } else if ((t[j].x() < t[i].x()) && t[j].y() == t[i].y()) {
            circleX = t[j].x() + radius*cos(atan(k));
            circleY = t[j].y() - radius*sin(atan(k)) * 0;

        } else {
            return;
        }
        p->drawEllipse(QPointF(circleX,circleY), radius/5,radius/5);
    }
}
