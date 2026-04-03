
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
class MyString {
  std::string m_str{};

public:
  MyString(std::string_view str) : m_str{str} {}
  friend std::ostream &operator<<(std::ostream &out, MyString mystr) {
    out << mystr.m_str;
    return out;
  }
  MyString operator()(int start, int length) {
    std::string_view vw{m_str};
    return {vw.substr(start, length)};
  }
};

int main() {
  MyString s{"Hello, world!"};
  std::cout << s(7, 5) << '\n'; // start at index 7 and return 5 characters

  return 0;
}
