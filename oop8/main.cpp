#include <QApplication>
#include "canvas.h"
#include "stategraph.h"
#include "graph.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Graph g;
    StateGraph sample(g);
    Canvas window(sample);
    window.show();

    return a.exec();
}
