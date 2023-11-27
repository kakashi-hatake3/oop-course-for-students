
#ifndef RATIONAL_H
#define RATIONAL_H
#include<iostream>
using namespace std;


class Rational{
public:
    int ch, zn;
    Rational();
    Rational(const int&);
    Rational operator*(Rational);
    Rational operator-(Rational);
    Rational operator+(Rational);
    Rational operator/(Rational);
    bool operator!=(Rational);
};


#endif // RATIONAL_H
