#include "Random.h"
#include <algorithm>
#include <array>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>

constexpr int ROW{4};
constexpr int COL{4};
constexpr int g_consoleLines{25};

class Direction {
public:
  enum Types {
    none,
    up,
    down,
    left,
    right,
  };

private:
  char m_dir{};

public:
  Types type{};
  Direction(char inp, Types new_type) : m_dir{inp}, type{new_type} {}
  Direction operator-() {
    switch (m_dir) {
    case 'w':
      return {'s', down};
    case 'a':
      return {'d', right};
    case 's':
      return {'w', up};
    default:
      return {'a', left};
    }
  }
  friend std::ostream &operator<<(std::ostream &out, Direction &dir) {
    switch (dir.m_dir) {
    case 'w':
      out << "Up";
      break;
    case 'a':
      out << "Left";
      break;
    case 's':
      out << "Back";
      break;
    default:
      out << "Right";
      break;
    }
    return out;
  }

  static Direction randomDir() {
    int num = Random::get(0, 3);
    switch (num) {
    case 0:
      return {'w', up};
    case 1:
      return {'a', left};
    case 2:
      return {'s', right};
    default:
      return {'d', down};
    }
  }
};

class Tile {
  int m_num{};

public:
  Tile(int num) : m_num{num} {}
  friend std::ostream &operator<<(std::ostream &out, Tile tile);
  bool isEmpty() { return (m_num == 0) ? true : false; }
  int getNum() { return m_num; }
  bool operator==(Tile other) { return m_num == other.m_num; }
  bool operator==(const Tile other) const { return m_num == other.m_num; }
};

std::ostream &operator<<(std::ostream &out, Tile tile) {
  if (tile.m_num == 0)
    out << " " << " " << "  ";
  else
    out << ((tile.m_num < 10) ? " " : "") << tile.m_num << "  ";
  return out;
}

template <typename T, std::size_t ROW, std::size_t COL>
using ArrayF2D = std::array<T, ROW * COL>;

template <typename T, std::size_t row, std::size_t col> class Array2DView {
  std::reference_wrapper<ArrayF2D<T, row, col>> m_arr{};

public:
  Array2DView(ArrayF2D<T, row, col> &arr) : m_arr{arr} {}
  T &operator()(int x, int y) { return m_arr.get()[x * COL + y]; }
  auto exposeArr() { return m_arr; }
  bool operator==(Array2DView arr) {
    if (m_arr.get() == arr.m_arr.get()) {
      return true;
    }
    return false;
  }
};
class Point {

public:
  std::size_t m_x{};
  std::size_t m_y{};
  Point(std::size_t x, std::size_t y) : m_x{x}, m_y{y} {}
  bool operator==(Point other) {
    if (m_x == other.m_x && m_y == other.m_y)
      return true;
    return false;
  }
  bool operator!=(Point other) { return !(*this == other); }
  Point getAdjacentPoint(Direction::Types type) {
    switch (type) {
    case Direction::up:
      return {m_x - 1, m_y};
    case Direction::down:
      return {m_x + 1, m_y};
    case Direction::left:
      return {m_x, m_y - 1};
    case Direction::right:
      return {m_x, m_y + 1};
    default:
      return {0, 0};
    }
  }
  bool isValid() {
    if (m_x <= 3 && m_x >= 0 && m_y <= 3 && m_y >= 0)
      return true;
    return false;
  }
};

class Board {
  ArrayF2D<Tile, ROW, COL> m_b{1, 2,  3,  4,  5,  6,  7,  8,
                               9, 10, 11, 12, 13, 14, 15, 0};
  Array2DView<Tile, ROW, COL> m_board{m_b};

public:
  friend std::ostream &operator<<(std::ostream &out, Board &board);

  void moveTile(Direction dir) {
    auto innerArr{m_board.exposeArr().get()};
    auto found{std::find(innerArr.begin(), innerArr.end(), Tile{0})};
    std::size_t index{static_cast<std::size_t>(found - innerArr.begin())};
    std::size_t x{index / COL};
    std::size_t y{index % COL};
    Direction tilemoves{-dir};
    Point new_point{Point{x, y}.getAdjacentPoint(tilemoves.type)};
    if (!new_point.isValid()) {
      return;
    }
    std::swap(m_board(x, y), m_board(new_point.m_x, new_point.m_y));
    return;
  }

  void randomize() {
    int randomTurns{Random::get(1000, 10000)};
    for (auto i{0u}; i < randomTurns; i++) {
      Direction dir{Direction::randomDir()};
      moveTile(dir);
    }
  }

  bool operator==(Board board) {
    if (m_board == board.m_board)
      return true;
    return false;
  }

  void check() {}
};

std::ostream &operator<<(std::ostream &out, Board &board) {
  for (auto n{0u}; n < g_consoleLines; n++) {
    std::cout << '\n';
  }
  for (auto i{0u}; i < ROW; i++) {
    for (auto j{0u}; j < COL; j++) {
      std::cout << board.m_board(i, j);
    }
    std::cout << std::endl;
  }
  return out;
}

namespace UserInput {

void ignoreInput() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool checkInput() {
  if (std::cin.fail()) {
    if (std::cin.eof()) {
      exit(0);
    }
    std::cin.clear();
    ignoreInput();
    return false;
  }
  return true;
}

bool checkInpVal(char c) {
  switch (c) {
  case 'w':
    std::cout << "You entered direction: up\n";
    return true;
  case 'a':
    std::cout << "You entered direction: left\n";
    return true;
  case 's':
    std::cout << "You entered direction: down\n";
    return true;
  case 'd':
    std::cout << "You entered direction: right\n";
    return true;
  case 'q':
    std::cout << "\n\nByeBye\n\n";
    exit(0);
  default:
    return false;
  }
}

char getInput() {
  char inp;
  while (true) {
    std::cin >> inp;
    if (!checkInput()) {
      continue;
    }
    if (!checkInpVal(inp)) {
      continue;
    }
    ignoreInput();
    break;
  }
  return inp;
}

Direction makeObj(char c) {
  switch (c) {
  case 'w':
    return {'w', Direction::up};
  case 'a':
    std::cout << "left\n";
    return {'a', Direction::left};
  case 's':
    std::cout << "down\n";
    return {'s', Direction::down};
  default:
    std::cout << "right\n";
    return {'d', Direction::right};
  }
} // namespace UserInput
} // namespace UserInput
// Your code goes here

// Note: save your main() from the prior step, as you'll need it again in the
// next step
int main() {
  Board final_board{};
  Board board{};
  board.randomize();
  std::cout << board;
  char inp;
  while (true) {
    inp = UserInput::getInput();
    Direction new_dir{UserInput::makeObj(inp)};
    board.moveTile(new_dir);
    std::cout << board;
    if (board == final_board)
      break;
  }
  std::cout << "\n\nYou won!!\n\n";
  return 0;
}
