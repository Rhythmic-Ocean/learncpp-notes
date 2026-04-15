#include "Random.h"
#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>

class Creature {
protected:
  std::string m_name{};
  char m_symbol{};
  int m_health_amt{};
  int m_dpa{};
  int m_gold{};

public:
  Creature(std::string_view name, char symb, int health_amt, int dpa, int gold)
      : m_name{name}, m_symbol{symb}, m_health_amt{health_amt}, m_dpa{dpa},
        m_gold{gold} {}

  std::string_view getName() { return m_name; }
  char getSymbol() { return m_symbol; }
  int getHealth() { return m_health_amt; }
  int getDpa() { return m_dpa; }
  int getGold() { return m_gold; }
  void reduceHealth(int red) { m_health_amt -= red; }
  bool isDead() { return m_health_amt <= 0; }
  void addGold(int gld) { m_gold += gld; }
};

class Player : public Creature {
protected:
  int m_level{1};

public:
  Player(std::string_view name) : Creature{name, '@', 10, 1, 0} {}
  void levelUp() {
    m_level++;
    m_dpa++;
  }
  int getLevel() { return m_level; }
  bool hasWon() { return m_level >= 20; }
  void DisplayPlayer() {
    std::cout << "Welcome, " << m_name << std::endl;
    std::cout << "You have " << m_health_amt << " health and are carrying "
              << m_gold << " gold." << std::endl;
  }
};

class Monster : public Creature {
public:
  enum Type { dragon, orc, slime, max_types };
  static inline Creature monsterData[]{
      {"dragon", 'D', 20, 4, 100},
      {"orc", 'o', 4, 2, 25},
      {"slime", 's', 1, 1, 10},
  };
  Monster(Type type) : Creature{monsterData[type]} {}
  static Monster getRandomMonster() {
    int rand{Random::get(0, 2)};
    return Monster{static_cast<Type>(rand)};
  }
};

void ignoreInput() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool checkInput() {
  if (std::cin.fail()) {
    if (std::cin.eof()) {
      exit(1);
    }
    std::cin.clear();
    ignoreInput();
    return false;
  }
  return true;
}

std::string getName() {
  std::string name;
  while (true) {
    std::cin >> name;
    if (!checkInput()) {
      std::cout << "Invalid name, please try again.";
      continue;
    }
    break;
  }
  return name;
}

class Action {
public:
  enum Type {
    fight,
    run,
  };
};

class Play {
public:
  enum Action { fight, run };
  static void play(Player &player, Monster &monster);
  static bool runn(Player &player, Monster &monster) {
    int succ{Random::get(0, 1)};
    switch (succ) {
    case 0:
      std::cout << "You successfully fled.\n";
      monster.reduceHealth(monster.getHealth());
      return true;
    default:
      std::cout << "You failed to flee.\n";
      std::cout << "The " << monster.getName() << " hits you for "
                << monster.getDpa() << " damange points." << std::endl;
      player.reduceHealth(monster.getDpa());
      return false;
    }
  }
  static void fightt(Player &player, Monster &monster) {
    std::cout << "You hit the slime for " << player.getDpa() << " damage.\n";
    monster.reduceHealth(player.getDpa());
    if (monster.isDead()) {
      std::cout << "You get " << monster.getGold() << " golds.\n";
      player.addGold(monster.getGold());
      player.levelUp();
      std::cout << "You are now level " << player.getLevel() << ".\n";
      return;
    }
    player.reduceHealth(monster.getDpa());
  }
};

Play::Action getOpt() {
  char opt;
  while (true) {
    std::cin >> opt;
    if (!checkInput()) {
      std::cout << "Invalid name, please try again.";
      continue;
    }
    switch (opt) {
    case 'f':
      return Play::fight;
    case 'r':
      return Play::run;
    default:
      std::cout << "Invalid option, please try again";
      continue;
    }
  }
}

void Play::play(Player &player, Monster &monster) {
  while (!player.isDead() && !monster.isDead()) {
    std::cout << "(R)un or (F)ight:";
    Action action{getOpt()};
    switch (action) {
    case run:
      runn(player, monster);
      break;
    case fight:
      fightt(player, monster);
      break;
    }
  }
}

int main() {
  std::cout << "Enter your name: ";
  std::string name{getName()};
  Player player{name};
  std::cout << "Welcome " << player.getName() << std::endl;
  while (true) {
    Monster monster{Monster::getRandomMonster()};
    std::cout << "You have encountered a " << monster.getName() << "("
              << monster.getSymbol() << ")\n";
    Play::play(player, monster);
    if (player.isDead()) {
      std::cout << "You died at level " << player.getLevel() << " with "
                << player.getGold() << " golds.\n";
      std::cout << "Too bad you can't take it.\n";
      break;
    }
    if (player.getLevel() >= 20) {
      std::cout << "You won! You have " << player.getGold() << " golds.\n";
    }
  }

  return 0;
}
