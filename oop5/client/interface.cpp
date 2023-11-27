
#include "interface.h"
#include <QDebug>



TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Практическая работа № 4");
    setFixedSize(600, 600);
    table = new QTableWidget(this);
    table->setGeometry(20, 20, 560, 500);
    table->setColumnCount(3);
    table->setRowCount(3);
    int num = 0;
    for(int i = 0; i < table->rowCount(); i++) {
        for(int j = 0; j < table->rowCount(); j++) {
            table->setItem(i, j, new QTableWidgetItem((QString::number(num)) + "/" + (QString::number(j + 1))));
            num++;
        }
    }
    transpose = new QPushButton("trans", this);
    transpose->setGeometry(60, 550, 50, 20);
    connect(transpose, SIGNAL(clicked()), this, SLOT(trans()));
    findRank = new QPushButton("rank", this);
    findRank->setGeometry(110, 550, 50, 20);
    connect(findRank, SIGNAL(clicked()), this, SLOT(rank()));
    findDet = new QPushButton("det", this);
    findDet->setGeometry(160, 550, 50, 20);
    connect(findDet, SIGNAL(clicked()), this, SLOT(det()));

    result_det = new QLabel(this);
    result_det->setGeometry(280, 520, 70, 30);
    result_rank = new QLabel(this);
    result_rank->setGeometry(280, 550, 70, 30);

    size_label = new QLabel("Size:", this);
    size_label->setGeometry(400, 520, 70, 30);

    size = new QLineEdit("3", this);
    size->setGeometry(400, 550, 70, 30);
    connect(size, SIGNAL(textChanged(QString)), this, SLOT(reSize()));


    answer = new QLabel("", this);
    answer->setGeometry(280, 520, 70, 60);

}
void TInterface::reSize() {
    Csize = size->text().toInt();
    table->setColumnCount(Csize);
    table->setRowCount(Csize);
    answer->clear();

}
void TInterface::det() {
    formRequest(3);

}
void TInterface::trans() {
    formRequest(2);
}
void TInterface::rank() {
    formRequest(1);
}

void TInterface::formRequest(int num) {
    QString msg;
    msg<<QString::number(Csize);
        for(int i = 0; i < Csize; i++) {
            for(int j = 0; j <  Csize; j++) {
            msg << table->item(i,j)->text().split("/")[0] << (table->item(i,j)->text().split("/")[1].toInt() == 0 ? QString::number(table->item(i,j)->text().split("/")[1].toInt() + 1):table->item(i,j)->text().split("/")[1]);
            }
        }
    msg<<QString().setNum(num);
    emit request(msg);
}
void TInterface::resAnswer(QString msg) {
    QString res;
    int pos = msg.length()-2;
    int t = msg[pos].digitValue();
    switch (t)
    {
    case  PRINT_ANSWER_RANK:
    {
            int i =0;

            while(msg[i] != ';') {
                res += msg[i];
                i++;
            }
            answer->setText("Rank = " + res);
            break;
    }
    case PRINT_TRANSPOSITION:
    {
            int count = 0;
            QStringList nums = msg.split(";");
            for(int i = 0; i < Csize; i++) {
                for(int j = 0; j < Csize; j++) {
                    table->item(i,j)->setText(nums[count] + "/" + nums[count + 1]);
                    count += 2;
                }
            }
    }
            break;
    case PRINT_ANSWER_DET:
    {
            qDebug() << msg;
            int i =0;
            QString num = "";
            QString del = "";
            while(msg[i] != ';') {
                num += msg[i];
                i++;
            }
            i++;
            while(msg[i] != ';') {
                del += msg[i];
                i++;
            }
            answer->setText("Det = " + num + " / " + del);
            break;
    }
    default: return;
    }
}



TInterface::~TInterface()
{
    delete[] table;
}


