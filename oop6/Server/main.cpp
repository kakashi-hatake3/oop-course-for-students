
#include "server.h"
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    Server a(argc, argv);

    return a.exec();
}
