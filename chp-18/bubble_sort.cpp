#include <cstddef>
#include <iostream>
#include <iterator>
#include <utility>
int main() {
  int array[]{6, 3, 2, 9, 7, 1, 5, 4, 8};
  std::size_t a_size{std::size(array)};
  std::size_t working_set{};
  bool no_swap_this_loop{false};
  for (std::size_t start{a_size - 1}; start > 0; --start) {
    working_set = start;
    for (std::size_t current{}; current < start; ++current) {
      if (array[current] > array[current + 1]) {
        std::swap(array[current], array[current + 1]);
        no_swap_this_loop = true;
      }
      working_set = current;
    }
    if (!no_swap_this_loop) {
      std::cout << "Loop terminated early at " << working_set + 1 << std::endl;
      break;
    }
    no_swap_this_loop = false;
  }
  for (int a : array) {
    std::cout << a;
  }
  std::cout << '\n';
  return 0;
}
