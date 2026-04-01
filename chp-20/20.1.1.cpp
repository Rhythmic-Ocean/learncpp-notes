#include <cstddef>
#include <functional>
#include <ios>
#include <iostream>
#include <limits>
#include <optional>

using ArithmeticFunction = std::function<int(int, int)>;

void ignoreInput() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool checkInput() {
  if (std::cin.fail()) {
    if (std::cin.eof()) {
      exit(1);
    }
    std::cin.clear();
    ignoreInput();
    return false;
  }
  ignoreInput();
  return true;
}

int getInt() {
  std::cout << "Enter an int\n";
  int num;
  while (true) {
    std::cin >> num;
    if (!checkInput()) {
      std::cout << "Bad input please try again!\n";
      continue;
    }
    break;
  }
  return num;
}

bool checkSign(char sign) {
  switch (sign) {
  case '*':
  case '+':
  case '-':
  case '/':
    return true;
  default:
    return false;
  }
}

char getOp() {
  std::cout << "Enter the sign\n";
  char sign;
  while (true) {
    std::cin >> sign;
    if (!checkInput()) {
      std::cout << "Bad input please try again!\n";
      continue;
    }
    if (!checkSign(sign)) {
      std::cout << "Bad input please try again!\n";
      continue;
    }
    break;
  }
  return sign;
}

int add(int a, int b) { return a + b; }

int sub(int a, int b) { return a - b; }

int mul(int a, int b) { return a * b; }

int divi(int a, int b) {
  return (b == 0) ? std::numeric_limits<int>::max() : a / b;
}

ArithmeticFunction getFnc(char sign) {
  switch (sign) {
  case '+':
    return add;
  case '-':
    return sub;
  case '/':
    return divi;
  default:
    return mul;
  }
}

int main() {
  int num1 = getInt();
  int num2 = getInt();
  char sign = getOp();
  ArithmeticFunction operation = getFnc(sign);
  std::cout << operation(num1, num2) << std::endl;
  return 0;
}
