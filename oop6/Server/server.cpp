#include "server.h"
#include "matrix.h"
#include "common.h"
#include "rational.h"
#include "real.h"
#include "squarematrix.h"
#include <complex.h>
Server::Server(int argc, char *argv[])
    : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 1235,
                        QHostAddress("127.0.0.1"), 1234};
    comm = new TCommunicator(pars, this);

    std::cout<<"connected";
    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}
Server::~Server() {

    delete comm;
}



void Server::recieve(QByteArray msg)

{    int type = msg.length() - 2;
    int t1 = msg[type]- '0';

   // SquareMatrix<number> matrix;
   // number cur;
    if(t1 == RATIONAL) {
      SquareMatrix matrix = SquareMatrix<Rational>();
        Rational cur;

      QString answer;

      QString cur_ = "";
      int y = 2;
      matrix.reSize(msg[0] - '0', msg[0] - '0');
      for(int i = 0; i < matrix.n; i++) {
          for(int j = 0; j < matrix.m; j++) {
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
      int pos = msg.length() - 4;
      int t = msg[pos]- '0';
      //qDebug()<<pos << t;
      switch (t)
      {
      case  PRINT_ANSWER_RANK:
          answer << QString::number(matrix.findRank());

          break;
      case PRINT_TRANSPOSITION:
          matrix.transpose();
          for(int i = 0; i < matrix.m; i++) {
              for(int j = 0; j < matrix.n; j++) {
                  cur = matrix.getEl(i, j);
                  qDebug() << cur.numerator << cur.devider;
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
    } else if(t1 == COMPLEX) {
        SquareMatrix matrix = SquareMatrix<complex>();
        complex cur;

        QString answer;

        QString cur_ = "";
        int y = 2;
        matrix.reSize(msg[0] - '0', msg[0] - '0');
        for(int i = 0; i < matrix.n; i++) {
            for(int j = 0; j < matrix.m; j++) {
                cur_ = "";
                while(msg[y] != ';') {
                    cur_ += msg[y];
                    y++;
                }
                cur.numerator = cur_.toDouble();
                cur_ = "";
                y++;
                while(msg[y] != ';') {
                    cur_ += msg[y];
                    y++;
                }
                y++;
                cur.devider =  cur_.toDouble();
                matrix.enter(cur, i, j);
            }
        }
        int pos = msg.length() - 4;
        int t = msg[pos]- '0';
        //qDebug()<<pos << t;
        switch (t)
        {
        case  PRINT_ANSWER_RANK:
            answer << QString::number(matrix.findRank());

            break;
        case PRINT_TRANSPOSITION:
            matrix.transpose();
            for(int i = 0; i < matrix.m; i++) {
                for(int j = 0; j < matrix.n; j++) {
                    cur = matrix.getEl(i, j);
                    qDebug() << cur.numerator << cur.devider;
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
    } else {
        SquareMatrix matrix = SquareMatrix<real>();
        real cur;
   QString answer;
   QString cur_ = "";
   int y = 2;
   matrix.reSize(msg[0] - '0', msg[0] - '0');
    for(int i = 0; i < matrix.n; i++) {
       for(int j = 0; j < matrix.m; j++) {
            cur_ = "";
           while(msg[y] != ';') {
                cur_ += msg[y];
                y++;
            }
            cur.numerator = cur_.toDouble();
            cur_ = "";
            y++;
            while(msg[y] != ';') {
                cur_ += msg[y];
                y++;
            }
            y++;
            cur.devider =  cur_.toDouble();
            matrix.enter(cur, i, j);
        }
    }
    int pos = msg.length() - 4;
    int t = msg[pos]- '0';
    //qDebug()<<pos << t;
    switch (t)
    {
    case  PRINT_ANSWER_RANK:
        answer << QString::number(matrix.findRank());

        break;
    case PRINT_TRANSPOSITION:
        matrix.transpose();
        for(int i = 0; i < matrix.m; i++) {
            for(int j = 0; j < matrix.n; j++) {
                cur = matrix.getEl(i, j);
                qDebug() << cur.numerator << cur.devider;
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
    comm->send(QByteArray().append(answer.toStdString()));}
}
