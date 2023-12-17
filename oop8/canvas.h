#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QFileDialog>
#include <QToolButton>
#include <QMouseEvent>
#include "stategraph.h"


class Canvas : public QWidget {
    Q_OBJECT
    StateGraph sample;

public:
    Canvas(StateGraph,QWidget *parent = 0);

public slots:
    void browse();

protected:
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent*);
    QWidget canvas;
};

#endif
