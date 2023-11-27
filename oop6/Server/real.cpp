
#include "real.h"

real::real()
{

}
real::real(const double& r)
{
    numerator = r;
    devider = 1;
}
real real::operator*(real c) {
    real t;
    t.numerator =numerator*c.numerator;
    t.devider = 1;
    return t;
}

real real::operator-(real c) {
   real t;
    t.numerator = numerator - c.numerator;
    t.devider = 1;
    return t;
}
real real::operator+(real c) {
    real t;
    t.numerator = numerator + c.numerator;
    t.devider = 1;
    return t;
}
real real::operator/(real c) {
    real t;
    t.numerator = numerator / c.numerator;

    t.devider = 1;
    return t;
}
bool real::operator!=(real c) {
    return(numerator != c.numerator);
}
