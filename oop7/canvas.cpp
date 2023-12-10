#include "canvas.h"

Canvas::Canvas(Sample f, QWidget *parent) : QWidget(parent) {
    sample = f;
    setFixedSize(320, 240);
    QToolButton* someButton = new QToolButton(this);
    someButton->setGeometry(5, 215, 310, 20);
    someButton->setText("Выбор графа для отрисовки");
    connect(someButton, SIGNAL(clicked()), this, SLOT(browse()));
}

void Canvas::browse(){
    QString fileName = "";
    fileName = QFileDialog::getOpenFileName(this, ("Open File"), "", ("Graph (*grp)"));
    if (fileName != ""){
        Graph g;
        g.set(fileName);
        this->sample = Sample(g);
        repaint();
    } else return;
}

void Canvas::paintEvent(QPaintEvent*) {
    QPainter p;
    p.begin(this);
    sample.paint(&p, QRect(5, 5, 310, 200));
    p.end();
}
