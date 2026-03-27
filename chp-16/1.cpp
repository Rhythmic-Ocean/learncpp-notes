#include <string_view>
#include <vector>

using namespace std::literals::string_view_literals;
int main() {
  std::vector a{2, 4, 6, 8, 10, 12, 14};
  const std::vector b{1.2, 3.4, 5.6, 7.8};
  const std::vector c{"Alex"sv, "Bard"sv, "Charles"sv, "Dave"sv};
  std::vector m{12};
  std::vector o(12, 0);
}
