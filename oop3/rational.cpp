#include <iostream>
#include <numeric>
using namespace std;

#include "rational.h"

Rational::Rational()
{

}

Rational::Rational(const int& a)
{
    ch = a;
    zn = 1;
}

Rational Rational::operator*(Rational c) {
    Rational t;

    t.ch = ch*c.ch;
    t.zn =zn*c.zn;
    if(t.zn == 0) {
        t.zn = 1;
    }
    if(t.ch == 0) {
        t.zn = 1;
    }
    return t;
}

Rational Rational::operator-(Rational c) {
    Rational t;
    int nok = lcm(zn, c.zn);

    if(zn == 0) {
        zn = 1;
    }
    t.ch = ch*(nok/zn) - c.ch*(nok/c.zn);
    t.zn = nok;
    return t;
}
Rational Rational::operator+(Rational c) {
    Rational t;
    int nok = lcm(abs(zn), abs(c.zn));

    t.ch = ch*(nok/zn) + c.ch*(nok/c.zn);
    t.zn = nok;

    if(t.ch == 0) {
        t.zn = 1;
    }
    return t;
}
Rational Rational::operator/(Rational c) {
    Rational t;
    if(c.ch == 0) {
        t.ch = 0;
        t.zn = 1;
        return t;
    }

    t.ch = ch*c.zn;
    t.zn =zn*c.ch;
    if(t.ch == 0) {
        t.zn = 1;
    }
    return t;
}
bool Rational::operator!=(Rational c) {
    return(ch != c.ch) || (zn != c.zn);
}


