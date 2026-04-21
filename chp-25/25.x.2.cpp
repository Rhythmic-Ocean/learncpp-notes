#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

class Shape {
public:
  virtual std::ostream &print(std::ostream &out) = 0;
  friend std::ostream &operator<<(std::ostream &out, Shape &shape) {
    return shape.print(out);
  }
  virtual ~Shape() = default;
};

class Point {
  int m_x{};
  int m_y{};

public:
  Point(int x = 0, int y = 0) : m_x{x}, m_y{y} {}
  friend std::ostream &operator<<(std::ostream &out, Point &point) {
    out << "Point(" << point.m_x << ", " << point.m_y << ")";
    return out;
  }
};

class Triangle : public Shape {
  Point m_p1{};
  Point m_p2{};
  Point m_p3{};

public:
  Triangle(const Point &p1, const Point &p2, const Point &p3)
      : m_p1{p1}, m_p2{p2}, m_p3{p3} {}
  std::ostream &print(std::ostream &out) override {
    out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ")";
    return out;
  }
};

class Circle : public Shape {
  Point m_center{};
  int m_rad{};

public:
  Circle(const Point &center, int rad) : m_center{center}, m_rad{rad} {}
  std::ostream &print(std::ostream &out) override {
    out << "Circle(" << m_center << ", radius " << m_rad << ")";
    return out;
  }
  int getRadius() { return m_rad; }
};

int getLargestRadius(std::vector<std::unique_ptr<Shape>> &v) {
  int largestRad{};
  for (auto &shape : v) {
    Circle *c = dynamic_cast<Circle *>(shape.get());
    if (c == nullptr)
      continue;
    if (c->getRadius() > largestRad) {
      largestRad = c->getRadius();
    }
  }
  return largestRad;
}

int main() {
  std::vector<std::unique_ptr<Shape>> v;
  v.push_back(std::move(std::make_unique<Circle>(Point{1, 2}, 7)));
  v.emplace_back(
      std::make_unique<Triangle>(Point{1, 2}, Point{3, 4}, Point{5, 6}));
  v.emplace_back(std::make_unique<Circle>(Point{7, 8}, 3));
  // print each shape in vector v on its own line here
  for (auto &shape : v) {
    std::cout << *shape.get() << '\n';
  }

  std::cout << "The largest radius is: " << getLargestRadius(v)
            << '\n'; // write this function

  return 0;
}
