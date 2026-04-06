
#include <cstdint>
#include <iostream>
class Average {
  double m_avg{};
  std::size_t m_count{};
  std::int32_t m_sum{};

public:
  friend std::ostream &operator<<(std::ostream &out, Average av) {
    out << av.m_avg;
    return out;
  }
  friend Average &operator+=(Average &avg, int num) {
    avg.m_sum += num;
    avg.m_count++;
    avg.m_avg = static_cast<double>(avg.m_sum) / avg.m_count;
    return avg;
  }
};

int main() {
  Average avg{};
  std::cout << avg << '\n';

  avg += 4;
  std::cout << avg << '\n'; // 4 / 1 = 4

  avg += 8;
  std::cout << avg << '\n'; // (4 + 8) / 2 = 6

  avg += 24;
  std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

  avg += -10;
  std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

  (avg += 6) += 10;         // 2 calls chained together
  std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

  Average copy{avg};
  std::cout << copy << '\n';

  return 0;
}
