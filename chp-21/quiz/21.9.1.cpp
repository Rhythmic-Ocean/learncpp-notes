// not using const_cast version of the stuff here cuz the setter and getter []
// as fundamentally different personalities
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
struct StudentGrade {
  std::string o_name{};
  char o_grade{};
  StudentGrade(std::string_view name, char grade)
      : o_name{name}, o_grade{grade} {}
};

class GradeMap {
  std::vector<StudentGrade> m_map{};

public:
  char &operator[](std::string_view str) {
    auto found{std::find_if(
        (this->m_map).begin(), (this->m_map).end(),
        [str](StudentGrade &student) { return str == student.o_name; })};
    if (found == m_map.end()) {
      m_map.emplace_back(StudentGrade{str, '\0'});
      return m_map.back().o_grade;
    }
    return (*found).o_grade;
  }
  const char &operator[](std::string_view str) const {
    auto found{std::find_if(
        (this->m_map).begin(), (this->m_map).end(),
        [str](StudentGrade student) { return str == student.o_name; })};
    assert(found != m_map.end() && "Student name not found in const GradeMap");
    return (*found).o_grade;
  }
};

// ...

int main() {
  GradeMap grades{};

  grades["Joe"] = 'A';
  grades["Frank"] = 'B';

  std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
  std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

  return 0;
}
