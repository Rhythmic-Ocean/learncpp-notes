#include <iostream>
#ifndef IO_FLAG
#define IO_FLAG
#include "io.h"
#endif // !Vd

int readNumber() {
  int num{};
  std::cin >> num;
  return num;
}

void writeAnswer(int answer) { std::cout << answer; }
