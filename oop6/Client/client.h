
#ifndef CLIENT_H
#define CLIENT_H




#include "communicator.h"
#include <QWidget>
#include <QUdpSocket>
#include <QDebug>
#include <interface.h>

#include<common.h>

class Client : public QWidget
{
    Q_OBJECT

private:

    TInterface* interface;


    TCommunicator* comm;

public:
    Client(QWidget *parent = nullptr);
    ~Client();

public slots:

    void fromCommunicator(QByteArray);
    void toCommunicator(QString);
};

#endif // CLIENT_H
