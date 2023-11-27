
#ifndef TINTERFACE_H
#define TINTERFACE_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QRadioButton>
#include <QtMath>
#include<common.h>

class TInterface : public QWidget

{
    Q_OBJECT
    QWidget* grid;
    QLineEdit** matrixCells;
    QLabel* answer;
    QLineEdit* size;
    QPushButton* findDet;
    QPushButton* transpose;
    QPushButton* findRank;
    QGridLayout* model;
    QRadioButton* cMode;
    QRadioButton* rationalMode;
    QRadioButton* realMode;


    void chandeSize();
    int Csize = 3;
public:
    void resAnswer(QString);
private:
    void formRequest(int num);


public slots:
    void det();
    void trans();
    void reSize();
    void rank();
signals:
     void request(QString);

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();
};

#endif // TINTERFACE_H
