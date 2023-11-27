#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    PRINT_ANSWER_RANK = 1,
    PRINT_TRANSPOSITION,
    PRINT_ANSWER_DET,
    RESIZE,
};

extern const char separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
