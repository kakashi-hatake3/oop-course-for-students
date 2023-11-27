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
enum modes {
    COMPLEX = 1,
    RATIONAL,
    REAL,

};

extern const char separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
