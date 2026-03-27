#include <cassert>
#include <iostream>
#include <vector>

namespace Items {
enum Types {
  health_potions,
  torches,
  arrows,
  max_items,
};
};

std::string_view enumToString(Items::Types type) {
  switch (type) {
  case Items::health_potions:
    return "health_potions";
  case Items::torches:
    return "torches";
  case Items::arrows:
    return "arrows";
  default:
    return "???";
  }
}

int main() {
  std::vector<int> items{1, 5, 10};
  assert(items.size() == Items::max_items);
  int total_items{};
  for (int i{}; i < Items::max_items; i++) {
    std::cout << "You have " << items[i] << ' '
              << enumToString(static_cast<Items::Types>(i)) << ".\n";
    total_items += items[i];
  }
  std::cout << "Total items is: " << total_items << std::endl;
}
