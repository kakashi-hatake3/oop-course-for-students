
#include "complex.h"

complex::complex()
{

}

complex::complex(const int& r)
{
    re = r;
    im = 0;
}

ostream& operator<<(ostream& os, complex c)
{
    if(c.im < 0) {
          os << c.re << c.im<<"i";
    } else {
          os << c.re << "+" << c.im<<"i";
    }

    return os;
}

complex complex::operator*(complex c) {
    complex t;
    t.re = re*c.re - im*c.im;
    t.im = re*c.im + im*c.re;
    return t;
}

complex complex::operator-(complex c) {
    complex t;
    t.re = re - c.re;
    t.im = im - c.im;
    return t;
}
complex complex::operator+(complex c) {
    complex t;
    t.re = re + c.re;
    t.im = im + c.im;
    return t;
}
complex complex::operator/(complex c) {
    complex t;
    t.re = (re * c.re + im*c.im) / (c.re * c.re + c.im + c. im);
    t.im = (c.re * im - re*c.im)/(c.re * c.re + c.im + c. im);
    return t;
}
bool complex::operator!=(complex c) {
    return(re != c.re) || (im != c.im);
}

istream& operator>>(istream& is, complex& c)
{
    is >> c.re >> c.im; // error
    return is;
}
