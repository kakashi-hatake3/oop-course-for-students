
#include "rational.h"
#include <numeric>
#include <QDebug>


Rational::Rational()
{

}
Rational::Rational(const int& a)
{
    numerator = a;
    devider = 1;
}

Rational Rational::operator*(Rational c) {
    Rational t;

    t.numerator = numerator*c.numerator;
    t.devider =devider*c.devider;
    if(t.devider == 0) {
        t.devider = 1;
    }
    if(t.numerator == 0) {
        t.devider = 1;
    }
    //qDebug() << numerator << devider<<c.numerator << c.devider<<t.numerator << t.devider;
    return t;
}

Rational Rational::operator-(Rational c) {
    Rational t;
    int g = std::lcm(devider, c.devider);

    if(devider == 0) {
        devider = 1;
    }

    t.numerator = numerator*(g/devider) - c.numerator*(g/c.devider);
    t.devider = g;
    // qDebug() << numerator << devider<<c.numerator << c.devider<<t.numerator << t.devider << g;
    if(t.numerator == 0) {
        t.devider = 1;
    }
    return t;
}
Rational Rational::operator+(Rational c) {
    Rational t;
    int g = std::lcm(abs(devider), abs(c.devider));

    t.numerator = numerator*(g/devider) + c.numerator*(g/c.devider);
    t.devider = g;

    if(t.numerator == 0) {
        t.devider = 1;
    }
    return t;
}
Rational Rational::operator/(Rational c) {
    Rational t;
    if(c.numerator == 0) {
        t.numerator = 0;
        t.devider = 1;
        return t;
    }

    t.numerator = numerator*c.devider;
    t.devider =devider*c.numerator;
    if(t.numerator == 0) {
        t.devider = 1;
    }
    // qDebug() << numerator << devider<<c.numerator << c.devider<<t.numerator << t.devider;
    return t;
}
bool Rational::operator!=(Rational c) {
    return(numerator != c.numerator) || (devider != c.devider);
}

