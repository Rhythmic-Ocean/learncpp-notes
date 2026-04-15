#include <iostream>
#include <string_view>

class Base {
protected:
  int m_value{};

public:
  Base(int value) : m_value{value} {}

  virtual ~Base() = default;

  virtual std::string_view getName() const { return "Base"; }
  int getValue() const { return m_value; }
};

class Derived : public Base {
public:
  Derived(int value) : Base{value} {}

  std::string_view getName() const override { return "Derived"; }
};

int main() {
  Derived derived{5};
  Base base{derived}; // what happens here?
  std::cout << "base is a " << base.getName() << " and has value "
            << base.getValue() << '\n';
  return 0;
}
