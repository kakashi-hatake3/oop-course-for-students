
#include "interface.h"
#include "matrix.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QTableWidget>


Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №3");
    setFixedSize(600, 600);

    table = new QTableWidget(this);
    table->setGeometry(20, 20, 560, 500);
    table->setColumnCount(3);
    table->setRowCount(3);
    for(int i = 0; i < table->rowCount(); i++) {
        for(int j = 0; j < table->rowCount(); j++) {
            table->setItem(i, j, new QTableWidgetItem((QString::number(matrix.getElement(i, j).ch)) + "/" + (QString::number(matrix.getElement(i, j).zn))));
        }
    }
    transpose = new QPushButton("trans", this);
    transpose->setGeometry(60, 550, 50, 20);
    connect(transpose, SIGNAL(clicked()), this, SLOT(transposition()));
    rank = new QPushButton("rank", this);
    rank->setGeometry(110, 550, 50, 20);
    connect(rank, SIGNAL(clicked()), this, SLOT(rankOfMatrix()));
    det = new QPushButton("det", this);
    det->setGeometry(160, 550, 50, 20);
    connect(det, SIGNAL(clicked()), this, SLOT(determination()));
    result_det = new QLabel(this);
    result_det->setGeometry(280, 520, 70, 30);
    result_rank = new QLabel(this);
    result_rank->setGeometry(280, 550, 70, 30);
    size_label = new QLabel("Size:", this);
    size_label->setGeometry(400, 520, 70, 30);
    size = new QLineEdit("3", this);
    size->setGeometry(400, 550, 70, 30);
    connect(size, SIGNAL(textChanged(QString)), this, SLOT(resize()));
}

Interface::~Interface()
{
    delete table;
    delete transpose;
    delete rank;
    delete det;
    delete result_det;
    delete result_rank;
    delete size;
    delete size_label;
}

void Interface::transposition(){
    changed();
    matrix.transpose();
    for(int i = 0; i < matrix._size; i++) {
        for(int j = 0; j < matrix._size; j++) {
            table->item(i, j)->setText((QString::number(matrix.getElement(i, j).ch)) + "/" + (QString::number(matrix.getElement(i, j).zn)));
        }
    }
}

void Interface::rankOfMatrix(){
    changed();
    result_rank->clear();
    int res = matrix.findRank();
    result_rank->setText("Rank= " + QString::number(res));
}

void Interface::determination(){
    changed();
    result_det->clear();
    QString det = (QString::number(matrix.activateDet().ch)) + "/" + (QString::number(matrix.activateDet().zn));
    result_det->setText("Det= " + det);
}

void Interface::resize(){
    int newSize = size->text().toInt();
    matrix.enterSize(newSize);
    matrix.reSize();
    table->setColumnCount(newSize);
    table->setRowCount(newSize);
    result_det->clear();
    result_rank->clear();
}

void Interface::changed(){
    number cur;
    for(int i = 0; i < table->rowCount(); i++) {
        for(int j = 0; j < table->rowCount(); j++) {
            cur.ch = table->item(i, j)->text().split("/")[0].toInt();
            cur.zn = table->item(i, j)->text().split("/")[1].toInt();
            matrix.enter(cur, i, j);
        }
    }
}


