#include "Random.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <limits>
#include <type_traits>
#include <vector>

void ignoreInput() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool checkInp() {
  if (std::cin.fail()) {
    if (std::cin.eof()) {
      exit(1);
    }
    std::cin.clear();
    ignoreInput();
    return false;
  }
  return true;
}

template <typename T> T getInt() {
  int num{};
  while (true) {
    std::cin >> num;
    if (!checkInp()) {
      std::cout << "Invalid input!\n";
      continue;
    }
    if constexpr (std::is_same<T, std::size_t>()) {
      if (num < 0) {
        std::cout << "This input cannot be negative.\n";
        continue;
      }
    }
    break;
  }
  return static_cast<T>(num);
}

int getRandom() {
  int num{Random::get(2, 4)};
  return num;
}

void generateSqrs(std::vector<int> &arr, int random, int start) {
  for (int &num : arr) {
    num = start * start * random;
    ++start;
  }
}

int main() {
  std::cout << "Start where? ";
  int start{getInt<int>()};
  std::cout << "How many? ";
  int many{getInt<int>()};
  int random{getRandom()};
  std::vector<int> arr(many);
  generateSqrs(arr, random, start);
  int num{};
  for (auto i{0u}; i < many; i++) {
    num = getInt<int>();
    auto found{std::find(arr.begin(), arr.end(), num)};
    if (found == arr.end()) {
      auto min_diff{
          std::min_element(arr.begin(), arr.end(), [num](auto a, auto b) {
            return (std::abs(num - a) < std::abs(num - b));
          })};
      std::cout << "Wrong answer! Try " << *min_diff << " next time!\n";
      return 0;
    }
  }
  return 0;
}
