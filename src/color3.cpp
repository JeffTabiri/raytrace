#include "color.h"
#include "vec3.h"
#include <iostream>

color operator+(const color& v1, const color& v2) {
  return color(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
};

color operator+(const color& v, const double c) {
  return color(v.e[0] + c, v.e[1] + c, v.e[2] + c);
};

color operator+(const double c, const color& v) {
  return v + c;
};

color operator+(const vec3 v, const color& c) {
  return color(c.x() + v.x(), c.y() + v.y(), c.z() + v.z());
}

color operator+(const color& c, const vec3& v) {
  return v + c;
}

color operator-(const color& v1, const color& v2) {
  return color(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
};

color operator-(const color& v, const double c) {
  return color(v.e[0] - c, v.e[1] - c, v.e[2] - c);
};

color operator-(const double c, const color& v) {
  return v - c;
};
 
color operator*(const color& v1, const color& v2) {
  return color(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
};

color operator*(const color& v, const double c) {
  return color(v.e[0] * c, v.e[1] * c, v.e[2] * c);
};

color operator*(const double c, const color& v) {
  return v * c;
};

color operator/(const color& v, const double c) {
  return v * (1/c);
};

color operator/(const double& c, const color& v) {
  return v / c;
};

void write_color(std::ostream &out, const color &p) {
  double r = p.x();
  double g = p.y();
  double b = p.z();

  double rbyte = int(255.999 * r);
  double gbyte = int(255.999 * g);
  double bbyte = int(255.999 * b);

  std::cout << rbyte << " " << gbyte << " " << bbyte<< "\n";
}
