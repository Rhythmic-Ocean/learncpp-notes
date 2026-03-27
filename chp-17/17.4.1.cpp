#include <functional>
#include <iostream>
#include <string_view>

struct Item {
  std::string_view name{};
  int gold{};
};

int main() {
  int a = 5;
  int b = 5;
  std::vector<std::reference_wrapper<int>> y{a};
  std::reference_wrapper<int> x{a};
  x.get() = 7;
  x = b;
  std::cout << y[0] << x.get();
}
