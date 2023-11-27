
#ifndef APPLICATION_H
#define APPLICATION_H




#include "matrix.h"
class Application
{
public:
    Application();
    int exec();
private:
    Matrix m;
    int menu();
};

#endif // APPLICATION_H
