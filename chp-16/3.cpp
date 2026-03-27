#include <cassert>
#include <iostream>
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
  std::vector v1{3, 8, 2, 5, 7, 8, 3};
  std::vector v2{5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6};

  std::pair<int, int> a{minMax(v1)};
  std::pair<double, double> b{minMax(v2)};
  std::cout << b.first << b.second;
}
