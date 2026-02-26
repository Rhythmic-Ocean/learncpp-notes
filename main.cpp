#include <iostream>

template <int N> // int non-type template parameter
void print() {
  std::cout << N << '\n';
}

template <char N> // char non-type template parameter
void print() {
  std::cout << N << '\n';
}

int main() {
  print<5>();   // ambiguous match with int N = 5 and char N = 5
  print<'c'>(); // ambiguous match with int N = 99 and char N = 'c'

  return 0;
}
