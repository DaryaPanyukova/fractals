#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

class Complex
{
    // z = x + yi;
public:
    Complex( long double,  long double);

    friend Complex operator+(Complex lhs, Complex rhs);
    friend Complex operator-(Complex lhs, Complex rhs);
    friend Complex operator*(Complex lhs, Complex rhs);
    friend Complex operator^(Complex lhs, int rhs);

     long double abs();
private:
     long double x_;
     long double y_;

};

#endif // COMPLEX_H
