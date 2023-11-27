
#include "interface.h"



TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Практическая работа № 6");
    resize(600 , 480);
    grid = new QWidget(this);
    grid->setFixedSize(400, 300);
    model = new QGridLayout(this);
    int num = 0;
    matrixCells = new QLineEdit*[Csize];
    for(int i = 0; i < Csize; i++) {
        matrixCells[i] = new QLineEdit[Csize*2];
    }
    for(int i = 0; i < Csize; i++) {
        for(int j = 0; j < Csize*2; j++) {

            matrixCells[i][j].setFixedHeight(25);
            matrixCells[i][j].setFixedWidth(25);
            if(j % 2 == 0) {
                matrixCells[i][j].setText(QString::number(num));
                model->addWidget(&matrixCells[i][j], i, j, 1, 20);
                num += 1;
            }else {
                matrixCells[i][j].setText(QString("1"));
                model->addWidget(&matrixCells[i][j], i, j);

            }


        }
    }
    grid->setLayout(model);
    findDet = new QPushButton("FindDet", this);
    findDet->setGeometry(0, 420, 60, 50);
    transpose = new QPushButton("Transpose",this);
    transpose->setGeometry(60, 420, 60, 50);
    findRank = new QPushButton("FindRank", this);
    findRank->setGeometry(120, 420, 60, 50);

    answer = new QLabel("Answer will be here", this);
    answer->setGeometry(350, 225, 200, 200 );

    size = new QLineEdit(this);
    size->setGeometry(180, 420, 100, 50);

    cMode = new QRadioButton("Комплексные числа", this);
    cMode->setGeometry(0, 405, 140, 10 );
    rationalMode = new QRadioButton("Рациональные числа", this);
    rationalMode->setGeometry(0, 380, 140, 10 );
    realMode = new QRadioButton("Вещественные числа", this);
    realMode->setGeometry(0, 355, 140, 10 );

    connect(size, SIGNAL(textChanged(QString)), this, SLOT(reSize()));
    connect(findDet, SIGNAL(clicked()), this, SLOT(det()));
    connect(findRank, SIGNAL(clicked()), this, SLOT(rank()));
    connect(transpose, SIGNAL(clicked()), this, SLOT(trans()));
}
void TInterface::reSize() {
    for(int i = 0; i < Csize; i++) {

        delete[] matrixCells[i];

    }
    delete[] matrixCells;
    Csize = size->text().toInt();
    if(Csize > 9 ) {
        Csize = 9;
    }
    else if(Csize < 3) {
       Csize = 3;
    }

    matrixCells = new QLineEdit*[Csize];
    for(int i = 0; i < Csize; i++) {
        matrixCells[i] = new QLineEdit[Csize*2];
    }
    for(int i = 0; i < Csize; i++) {
        for(int j = 0; j < Csize*2; j++) {

            matrixCells[i][j].setFixedHeight(25);
            matrixCells[i][j].setFixedWidth(25);
            if(j % 2 == 0) {
                model->addWidget(&matrixCells[i][j], i, j, 1, 20);
            }else {
                model->addWidget(&matrixCells[i][j], i, j);
            }
            matrixCells[i][j].setText(QString("1"));
        }
    }

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
            for(int j = 0; j <  Csize*2; j++) {
                if(j % 2 == 0) {
                    msg <<  matrixCells[i][j].text() << (matrixCells[i][j + 1].text().toInt() == 0 ? QString::number(matrixCells[i][j + 1].text().toInt() + 1):matrixCells[i][j + 1].text());
                }

            }
        }
    msg<<QString().setNum(num);
     if(cMode->isChecked())  {
            msg<<QString().setNum(COMPLEX);
     }   else if(rationalMode->isChecked()) {
             msg<<QString().setNum(RATIONAL);

     } else if(realMode->isChecked()) {
              msg<<QString().setNum(REAL);
     }
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
            for(int i = 0; i < Csize; i++) {
                for(int j = 0; j < Csize*2; j++) {
                    while(msg[count] != ';') {
                        res += msg[count];
                        count++;
                    }
                    matrixCells[i][j].setText(res);
                    count++;
                    res = "";
                }
            }
    }
            break;
    case PRINT_ANSWER_DET:
    {
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

            if(cMode->isChecked())  {
               answer->setText("Det = " + num + "+ i " + del);
            }   else if(rationalMode->isChecked()) {
               answer->setText("Det = " + num + " / " + del);

            } else if(realMode->isChecked()) {
               answer->setText("Det = " + num);

            }

            break;
    }
    default: return;
    }
}



TInterface::~TInterface()
{
    for(int i = 0; i < Csize; i++) {

        delete[] matrixCells[i];

    }
    delete[] matrixCells;
    delete model;
}


