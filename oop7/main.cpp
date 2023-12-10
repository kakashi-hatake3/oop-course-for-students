#include <QApplication>
#include "canvas.h"
#include "sample.h"
#include "graph.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Graph g;
    Sample sample(g);
    Canvas window(sample);
    window.show();

    return a.exec();
}
