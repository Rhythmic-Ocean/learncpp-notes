#include <cassert>
#include <cstdint>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>

void ignoreInput() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool check_input() {
  if (std::cin.fail()) {
    if (std::cin.eof()) {
      exit(0);
    }
    std::cin.clear();
    ignoreInput();
    return false;
  }
  return true;
}

class FixedPoint2 {
  std::int16_t m_bpoint{};
  std::int8_t m_apoint{};

public:
  FixedPoint2(std::int16_t bpoint, std::int8_t apoint)
      : m_bpoint{bpoint}, m_apoint{apoint} {}

  FixedPoint2(double num) {
    m_bpoint = std::abs(static_cast<std::int16_t>(num));
    int test = std::abs((static_cast<int>(num * 1000) % 1000));
    m_apoint =
        static_cast<std::int8_t>((test % 10 < 5) ? test / 10 : (test / 10 + 1));
    if (num < 0) {
      m_apoint = -m_apoint;
      m_bpoint = -m_bpoint;
    }
  }

  explicit operator double() {
    double num{static_cast<double>(m_bpoint)};
    if ((m_apoint ^ m_bpoint) >= 0) {
      num += (static_cast<double>(m_apoint) / 100);
    } else {
      num = std::abs(num) + std::abs((static_cast<double>(m_apoint) / 100));
      num = -num;
    }
    return num;
  }

  explicit operator double() const {
    double num{static_cast<double>(m_bpoint)};
    if ((m_apoint ^ m_bpoint) >= 0) {
      num += (static_cast<double>(m_apoint) / 100);
    } else {
      num = std::abs(num) + std::abs((static_cast<double>(m_apoint) / 100));
      num = -num;
    }
    return num;
  }
  FixedPoint2 &operator-() {
    double num = static_cast<double>(*this);
    if (num < 0) {
      m_apoint = std::abs(m_apoint);
      m_bpoint = std::abs(m_bpoint);
    } else {
      m_apoint = -m_apoint;
      m_bpoint = -m_bpoint;
    }
    return *this;
  }
  friend FixedPoint2 operator+(const FixedPoint2 &fp1, const FixedPoint2 &fp2) {
    double sum = static_cast<double>(fp1) + static_cast<double>(fp2);
    return {sum};
  }
  friend std::ostream &operator<<(std::ostream &out, FixedPoint2 &fp2) {
    out << fp2.m_bpoint << "." << static_cast<int>(fp2.m_apoint);
    return out;
  }
  friend bool operator==(const FixedPoint2 &fp1, const FixedPoint2 &fp2) {
    return static_cast<double>(fp1) == static_cast<double>(fp2);
  }
  friend std::istream &operator>>(std::istream &in, FixedPoint2 &fp) {
    double num{};
    while (true) {
      in >> num;
      if (!check_input()) {
        std::cout << "Bad input, please try again!";
        continue;
      }
      break;
    }
    fp = FixedPoint2{num};
    return in;
  }
};

int main() {
  assert(FixedPoint2{0.75} == FixedPoint2{0.75});    // Test equality true
  assert(!(FixedPoint2{0.75} == FixedPoint2{0.76})); // Test equality false

  // Test additional cases -- h/t to reader Sharjeel Safdar for these test cases
  FixedPoint2 fp{0.75};
  std::cout << fp << std::endl;
  assert(FixedPoint2{0.75} + FixedPoint2{1.23} ==
         FixedPoint2{1.98}); // both positive, no decimal overflow
  assert(FixedPoint2{0.75} + FixedPoint2{1.50} ==
         FixedPoint2{2.25}); // both positive, with decimal overflow
  assert(FixedPoint2{-0.75} + FixedPoint2{-1.23} ==
         FixedPoint2{-1.98}); // both negative, no decimal overflow
  assert(FixedPoint2{-0.75} + FixedPoint2{-1.50} ==
         FixedPoint2{-2.25}); // both negative, with decimal overflow
  assert(FixedPoint2{0.75} + FixedPoint2{-1.23} ==
         FixedPoint2{-0.48}); // second negative, no decimal overflow
  assert(FixedPoint2{0.75} + FixedPoint2{-1.50} ==
         FixedPoint2{-0.75}); // second negative, possible decimal overflow
  assert(FixedPoint2{-0.75} + FixedPoint2{1.23} ==
         FixedPoint2{0.48}); // first negative, no decimal overflow
  assert(FixedPoint2{-0.75} + FixedPoint2{1.50} ==
         FixedPoint2{0.75}); // first negative, possible decimal overflow

  FixedPoint2 a{-0.48};
  assert(static_cast<double>(a) == -0.48);
  assert(static_cast<double>(-a) == 0.48);

  std::cout << "Enter a number: "; // enter 5.678
  std::cin >> a;
  std::cout << "You entered: " << a << '\n';
  assert(static_cast<double>(a) == 5.68);

  return 0;
}
