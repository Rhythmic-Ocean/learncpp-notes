#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

static int name_count{};

void ignoreInput() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool checkInput() {
  if (std::cin.fail()) {
    if (std::cin.eof())
      exit(0);
    std::cin.clear();
    ignoreInput();
    return true;
  }
  return false;
}

std::size_t getLength() {
  std::size_t length{};
  while (true) {
    std::cout << "Enter how many names you want to enter!\n";
    std::cin >> length;
    if (checkInput()) {
      std::cout << "Invalid input for length, please try again.\n";
      continue;
    }
    break;
  }
  ignoreInput();
  return length;
}

void getString(std::string &name) {
  name_count++;
  while (true) {
    std::cout << "Enter your name no. " << name_count << std::endl;
    std::getline(std::cin, name);
    if (checkInput()) {
      std::cout << "Invalid input for name, please try again.";
      continue;
    }
    break;
  }
  return;
}

int main() {
  std::size_t length{getLength()};
  std::vector<std::string> name(length);
  for (auto &n : name) {
    getString(n);
  }
  std::sort(name.begin(), name.end());
  for (std::string_view n : name) {
    std::cout << n << std::endl;
  }

  return 0;
}
