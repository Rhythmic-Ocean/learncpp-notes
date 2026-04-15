#include <iostream>
#include <string_view>

class Fruit {
protected:
  std::string m_name{};
  std::string m_color{};

public:
  Fruit(std::string_view name, std::string_view color)
      : m_name{name}, m_color{color} {}
};

class Apple : public Fruit {
public:
  Apple(std::string_view color = "red", std::string name = "apple")
      : Fruit{name, color} {}
  std::string_view getName() { return m_name; }
  std::string_view getColor() { return m_color; }
};

class Banana : public Fruit {
public:
  Banana(std::string_view color = "yellow", std::string name = "banana")
      : Fruit{name, color} {}
  std::string_view getName() { return m_name; }
  std::string_view getColor() { return m_color; }
};

class GrannySmith : public Apple {
public:
  GrannySmith() : Apple("green", "granny smith apple") {}
};

int main() {
  Apple a{"red"};
  Banana b;
  GrannySmith c;

  std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
  std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
  std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

  return 0;
}
