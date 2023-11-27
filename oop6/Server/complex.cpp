
#include "complex.h"

complex::complex()
{

}

complex::complex(const int& r)
{
    numerator = r;
    devider = 0;
}

ostream& operator<<(ostream& os, complex c)
{
    if(c.devider < 0) {
        os << c.numerator << c.devider<<"i";
    } else {
        os << c.numerator << "+" << c.devider<<"i";
    }

    return os;
}

complex complex::operator*(complex c) {
    complex t;
    t.numerator =numerator*c.numerator - devider*c.devider;
    t.devider = numerator*c.devider + devider*c.numerator;
    return t;
}

complex complex::operator-(complex c) {
    complex t;
    t.numerator = numerator - c.numerator;
    t.devider = devider - c.devider;
    return t;
}
complex complex::operator+(complex c) {
    complex t;
    t.numerator = numerator + c.numerator;
    t.devider = devider + c.devider;
    return t;
}
complex complex::operator/(complex c) {
    complex t;
    t.numerator = (numerator * c.numerator + devider*c.devider
                   ) / (c.numerator * c.numerator + c.devider + c.devider);
    t.devider = (c.numerator * devider - numerator*c.devider)/(c.numerator * c.numerator + c.devider + c. devider);
    return t;
}
bool complex::operator!=(complex c) {
    return(numerator != c.numerator) || (devider != c.devider);
}

istream& operator>>(istream& is, complex& c)
{
    is >> c.numerator >> c.devider; // error
    return is;
}
