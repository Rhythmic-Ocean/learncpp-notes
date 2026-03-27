#include <ios>
#include <iostream>
#include <limits>

constexpr int arr[]{0, 1, 4, 9, 16, 25, 36, 49, 64, 81};

int main() {
  std::cout << "Enter one digit, -1 to quit.\n";
  int a{};
  while (true) {
    std::cin >> a;
    if (!std::cin) {
      if (std::cin.eof())
        exit(0);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Bad input, please try again.\n";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (a == -1)
      return 0;
    if (a > 9 || a < 0) {
      std::cout << "Bad input, please try again.\n";
      continue;
    }
    for (int num : arr) {
      if (a == num) {
        std::cout << a << " is a perfect square!\n";
        return 0;
      }
    }
    std::cout << a << " is not a perf square!\n";
  }
  return 0;
}
