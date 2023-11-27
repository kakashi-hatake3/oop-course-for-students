
#ifndef RATIONAL_H
#define RATIONAL_H




class Rational
{
public:
    Rational();
    int numerator;
    int devider;

    Rational(const int&);
    Rational operator*( Rational);
    Rational operator-( Rational);
    Rational operator+( Rational);
    Rational operator/( Rational);
    Rational reduction(Rational t);
    bool operator!=( Rational);

private:

};

#endif // RATIONAL_H
