#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QFileDialog>
#include <QToolButton>
#include "sample.h"


class Canvas : public QWidget {
    Q_OBJECT
    Sample sample;

public:
    Canvas(Sample,QWidget *parent = 0);

public slots:
    void browse();

protected:
    void paintEvent(QPaintEvent*);
    QWidget canvas;


};

#endif
