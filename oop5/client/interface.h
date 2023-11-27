
#ifndef TINTERFACE_H
#define TINTERFACE_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtMath>
#include<common.h>
#include <QTableWidget>

class TInterface : public QWidget
{
    Q_OBJECT
    QLabel* answer;
    QLineEdit* size;
    QPushButton* transpose;
    void chandeSize();
    int Csize = 3;
    QTableWidget *table;
    QPushButton* findRank;
    QPushButton* findDet;
    QLabel* result_det;
    QLabel* result_rank;
    QLabel* size_label;
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
