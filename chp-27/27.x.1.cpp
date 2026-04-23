#include <exception>
#include <ios>
#include <iostream>
#include <limits>
#include <stdexcept>
class Fraction {
  int m_num{};
  int m_den{1};

public:
  Fraction(int num, int den) : m_num{num}, m_den{den} {
    if (den == 0) {
      throw std::runtime_error("Denominator cannot be zero.");
    }
  }
};

void ignoreInp() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool checkInt() {
  if (std::cin.fail()) {
    if (std::cin.eof())
      exit(0);
    std::cin.clear();
    ignoreInp();
    return false;
  }
  return true;
}

int getInt() {
  int num{};
  while (true) {
    std::cin >> num;
    if (!checkInt()) {
      std::cout << "invalid inp pls try again\n";
      continue;
    }
    ignoreInp();
    break;
  }
  return num;
}

int main() {
  std::cout << "Enter first num: ";
  int a{getInt()};
  std::cout << "Enter sec num: ";
  int b{getInt()};
  try {
    Fraction frac = Fraction{a, b};
  } catch (std::exception &err) {
    std::cerr << "Error happened: " << err.what() << "\n";
  }
  return 0;
}
