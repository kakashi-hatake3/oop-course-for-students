
#include "tmatrix.h"

TMatrix::TMatrix(number aa, number bb, number cc, number dd)
{
    a = aa;
    b = bb;
    c = cc;
    d = dd;

}

ostream& operator<< (ostream& os, TMatrix& matrix){
    os << endl << matrix.a << " " << matrix.b << endl << matrix.c << " " << matrix.d << endl;
    return os;
}
