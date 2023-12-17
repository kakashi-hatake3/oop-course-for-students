#include "graph.h"
#include <QDebug>

Graph::Graph()
{
    this->adj = new Matrix<int>(4, 4);
    this->adj->insert(0, 2, 1);
    this->adj->insert(1, 3, 1);
}

void Graph::set(QString f){
    QFile file(f);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    this->graph_size = in.readLine().toInt();
    this->adj->setSize(this->graph_size, this->graph_size);
    QStringList matr = in.readLine().split(" "), matr2;
    int count = 0;
    for (int i = 0; i < this->graph_size; i++){
        for (int j = 0; j < this->graph_size; j++){
            this->adj->insert(i, j, matr[count].toInt());
            count++;
        }
    }
    file.close();
}

int Graph::size(){
    return this->graph_size;
}

int Graph::retrieve(int i, int j){
    return this->adj->retrieve(i, j);
}
