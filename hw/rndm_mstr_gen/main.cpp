#include "Random.h"
#include <iostream>
#include <string>

class Monster {
public:
  enum Type {
    dragon,
    goblin,
    ogre,
    orc,
    skeleton,
    troll,
    vampire,
    zombie,
    maxMonsterTypes,
  };

private:
  Type m_type{};
  std::string m_name{};
  std::string m_roar{};
  int m_hitPts{};

public:
  Monster(const Type type, const std::string_view name,
          const std::string_view roar, const int hPts)
      : m_type{type}, m_name{name}, m_roar{roar}, m_hitPts{hPts} {}
  void print() const;
};

std::string_view getTypeString(Monster::Type type) {
  switch (type) {
  case Monster::dragon:
    return "Dragon";
  case Monster::goblin:
    return "Goblin";
  case Monster::ogre:
    return "Orge";
  case Monster::skeleton:
    return "Skeleton";
  case Monster::troll:
    return "Troll";
  case Monster::vampire:
    return "Vampire";
  case Monster::zombie:
    return "Zombie";
  case Monster::orc:
    return "Orc";
  default:
    return "???";
  }
}

void Monster::print() const {
  std::string_view type = getTypeString(m_type);
  std::cout << m_name << " the " << type << " has " << m_hitPts
            << " hit points and says " << m_roar << "." << std::endl;
}

namespace MonsterGenerator {

std::string_view getName(int num) {
  switch (num) {
  case 0:
    return "Brain";
  case 1:
    return "Sam";
  case 2:
    return "Bones";
  case 3:
    return "Holmes";
  case 4:
    return "Pecker";
  case 5:
    return "Hambulgler";
  default:
    return "???";
  }
}

std::string_view getRoar(int num) {
  switch (num) {
  case 0:
    return "*rattle*";
  case 1:
    return "RAHHH!!";
  case 2:
    return "BOO!!";
  case 3:
    return "Meow~";
  case 4:
    return "*slurp*";
  case 5:
    return "HoOHOhhoO";
  default:
    return "???";
  }
}

Monster generate() {

  return {static_cast<Monster::Type>(Random::get(0, 7)),
          getName(Random::get(0, 5)), getRoar(Random::get(0, 5)),
          Random::get(1, 10)};
}
} // namespace MonsterGenerator

int main() {
  Monster m{MonsterGenerator::generate()};
  m.print();

  return 0;
}
