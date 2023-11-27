#include "client.h"


Client::Client(QWidget *parent)
    : QWidget(parent)
{

    TCommParams props = {QHostAddress("127.0.0.1"), 1234, QHostAddress("127.0.0.1"), 1235};
    comm = new TCommunicator(props, this);

    interface = new TInterface();
    interface->show();

    connect(interface, SIGNAL(request(QString)), this, SLOT(toCommunicator(QString)));
    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(fromCommunicator(QByteArray)));
}

Client::~Client()
{
    delete interface;
    delete comm;

}

void Client::fromCommunicator(QByteArray msg) {
    interface->resAnswer(QString(msg));
}

void Client::toCommunicator(QString msg) {
    comm->send(QByteArray().append(msg.toStdString()));
    return;
}

