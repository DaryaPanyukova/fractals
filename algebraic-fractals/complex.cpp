#include "complex.h"

Complex::Complex(long double x0, long double y0): x_(x0), y_(y0){};

Complex operator+(Complex lhs, Complex rhs) {
   lhs.x_ += rhs.x_;
   lhs.y_ += rhs.y_;
   return lhs;
}

Complex operator-(Complex lhs, Complex rhs) {
   lhs.x_ -= rhs.x_;
   lhs.y_ -= rhs.y_;
   return lhs;
}

Complex operator*(Complex lhs, Complex rhs) {
  long double a1 = lhs.x_, b1 = lhs.y_;
  long double a2 = rhs.x_, b2 = rhs.y_;

  lhs.x_ = a1 * a2 - b1 * b2;
  lhs.y_ = a1 * b2 + a2 * b1;
  return lhs;
}

Complex operator^(Complex lhs, int rhs){
    for (int i = 1; i < rhs; ++i) {
        lhs = lhs * lhs;
    }
    return lhs;
}

long double Complex::abs() {
    return sqrt(this->x_ * this->x_ + this->y_ * this->y_);
}
