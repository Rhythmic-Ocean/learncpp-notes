#include <iostream>

template <typename T1, typename T2> class Pair {
  T1 m_x{};
  T2 m_y{};

public:
  Pair(T1 x, T2 y) : m_x{x}, m_y{y} {}
  const T1 &first() const { return m_x; }
  const T2 &second() const { return m_y; }
};

template <typename T> class Pair<std::string, T> {
  std::string m_x{};
  T m_y{};

public:
  Pair(std::string_view x, T y) : m_x{x}, m_y{y} {}
  const std::string_view first() const { return m_x; }
  const T &second() const { return m_y; }
};

template <typename T> class StringValuePair : public Pair<std::string, T> {
public:
  StringValuePair(std::string_view x, T y) : Pair<std::string, T>{x, y} {}
};

int main() {
  StringValuePair<int> svp{"Hello", 5};
  std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

  return 0;
}
