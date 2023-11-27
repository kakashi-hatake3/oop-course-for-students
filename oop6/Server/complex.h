

#ifndef COMPLEX_H
#define COMPLEX_H


#include<iostream>
using namespace std;

class complex
{


public:
    complex();
    complex(const int&);
    complex operator*(complex);
    complex operator-(complex);
    complex operator+(complex);
    complex operator/(complex);
    bool operator!=(complex);
    friend ostream& operator<<(ostream&, complex);
    friend istream& operator>>(istream&, complex&);
    double numerator, devider;
};

#endif // COMPLEX_H
