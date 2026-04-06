#include <iostream>
#include <ostream>

class IntArray {
  int *m_nums;
  int m_count{};

public:
  IntArray(int count) : m_nums{new int[count]}, m_count{count} {}
  int &operator[](int index) { return *(m_nums + index); }
  const int &operator[](int index) const { return *(m_nums + index); }
  friend std::ostream &operator<<(std::ostream &out, IntArray arr) {
    int *begin = arr.m_nums;
    int *end = arr.m_nums + arr.m_count;
    for (; begin < end; begin++) {
      out << *begin << " ";
    }
    out << std::endl;
    return out;
  }
};

IntArray fillArray() {
  IntArray a(5);

  a[0] = 5;
  a[1] = 8;
  a[2] = 2;
  a[3] = 3;
  a[4] = 6;

  return a;
}

int main() {
  IntArray a{fillArray()};

  std::cout << a << '\n';

  auto &ref{
      a}; // we're using this reference to avoid compiler self-assignment errors
  a = ref;

  IntArray b(1);
  b = a;

  a[4] = 7;

  std::cout << b << '\n';

  return 0;
}
