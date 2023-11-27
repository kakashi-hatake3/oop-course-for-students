#include "server.h"
#include "matrix.h"
#include "common.h"
Server::Server(int argc, char *argv[])
    : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 1235,
                        QHostAddress("127.0.0.1"), 1234};
    comm = new TCommunicator(pars, this);
    matrix = Matrix();
    std::cout<<"connected";
    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}
Server::~Server() {

    delete comm;
}

void Server::recieve(QByteArray msg)
{

    QString answer;
    number cur;
   QString cur_ = "";
   int y = 2;
   matrix.reSize(msg[0] - '0');
    for(int i = 0; i < matrix._size; i++) {
       for(int j = 0; j < matrix._size; j++) {
            cur_ = "";
           while(msg[y] != ';') {
                cur_ += msg[y];
                y++;
            }
            cur.numerator = cur_.toInt();
            cur_ = "";
            y++;
            while(msg[y] != ';') {
                cur_ += msg[y];
                y++;
            }
            y++;
            cur.devider =  cur_.toInt();
            matrix.enter(cur, i, j);
        }
    }
    int pos = msg.length() - 2;
    int t = msg[pos]- '0';
    //qDebug()<<pos << t;
    switch (t)
    {
    case  PRINT_ANSWER_RANK:
        answer << QString::number(matrix.findRank());

        break;
    case PRINT_TRANSPOSITION:
        matrix.transpose();
        for(int i = 0; i < matrix._size; i++) {
            for(int j = 0; j < matrix._size; j++) {
                cur = matrix.getEl(i, j);
                answer<<QString::number(cur.numerator) << QString::number(cur.devider);
            }
        }

        break;
    case PRINT_ANSWER_DET:
        answer << QString::number(matrix.activateDet().numerator) << QString::number(matrix.activateDet().devider);
        break;
    default: return;
    }
    answer<<QString().setNum(t);
    comm->send(QByteArray().append(answer.toStdString()));
}
