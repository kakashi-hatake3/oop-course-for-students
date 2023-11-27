
#ifndef REAL_H
#define REAL_H




class real
{
public:
    real();

    real(const double&);
    real operator*(real);
    real operator-(real);
    real operator+(real);
    real operator/(real);
    bool operator!=(real);
    double numerator, devider = 1;
};

#endif // REAL_H
