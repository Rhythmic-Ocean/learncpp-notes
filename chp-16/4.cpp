
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <vector>

template <typename T> std::pair<T, T> minMax(const std::vector<T> &arr) {
  if (arr.size() == 0)
    return {0, 0};
  T min{arr[0]};
  T max{arr[0]};
  for (T val : arr) {
    if (val < min)
      min = val;
    if (val > max)
      max = val;
  }
  return {min, max};
}

int main() {
  std::vector<int> v1{};
  int temp{};
  while (1) {
    std::cin >> temp;
    if (!std::cin) {
      if (std::cin.eof()) {
        exit(0);
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (temp == -1) {
      break;
    }
    v1.push_back(temp);
  }
  std::pair<int, int> a{minMax(v1)};
  std::cout << a.first << " " << a.second << std::endl;
}
