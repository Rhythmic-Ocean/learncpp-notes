#include <algorithm>
#include <array>
#include <iostream>
#include <string>

struct Student {
  std::string name{};
  int points{};
};

int main() {
  std::array<Student, 8> arr{{{"Albert", 3},
                              {"Ben", 5},
                              {"Christine", 2},
                              {"Dan", 8}, // Dan has the most points (8).
                              {"Enchilada", 4},
                              {"Francis", 1},
                              {"Greg", 3},
                              {"Hagrid", 5}}};
  auto max_studuent{std::max_element(arr.begin(), arr.end(),
                                     [](auto &student1, auto &student2) {
                                       if (student1.points < student2.points)
                                         return true;
                                       return false;
                                     })};
  std::cout << max_studuent->name << std::endl;
}
