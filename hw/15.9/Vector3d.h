#pragma once
class Vector3d {
private:
  double m_x{};
  double m_y{};
  double m_z{};

public:
  Vector3d(double x, double y, double z);

  void print() const;
  friend class Point3d;
};
