#include <iostream>
#include <numeric>

class Fraction {
  int m_num{};
  int m_den{1};

public:
  explicit Fraction(int num, int den = 1)
      : m_num{num / std::gcd(num, den)}, m_den{den / std::gcd(num, den)} {}
  void print() { std::cout << this->m_num << "/" << this->m_den << std::endl; }
  friend Fraction operator*(const Fraction &f1, const Fraction &f2);
  friend Fraction operator*(const Fraction &f1, int val);
  friend Fraction operator*(int val, const Fraction &f1);
};

Fraction operator*(const Fraction &f1, const Fraction &f2) {
  int num = f1.m_num * f2.m_num;
  int den = f1.m_den * f2.m_den;
  return Fraction{num, den};
}

Fraction operator*(const Fraction &f1, int val) {
  int num = f1.m_num * val;
  int den = f1.m_den;
  return Fraction{num, den};
}

Fraction operator*(int val, const Fraction &f1) { return f1 * val; }

int main() {
  Fraction f1{2, 5};
  f1.print();

  Fraction f2{3, 8};
  f2.print();

  Fraction f3{f1 * f2};
  f3.print();

  Fraction f4{f1 * 2};
  f4.print();

  Fraction f5{2 * f2};
  f5.print();

  Fraction f6{Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4}};
  f6.print();

  Fraction f7{0, 6};
  f7.print();

  return 0;
}
