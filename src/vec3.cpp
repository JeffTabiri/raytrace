#include "vec3.h"
#include <cmath>

vec3 operator+(const vec3& v1, const vec3& v2) {
  return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
};

vec3 operator+(const vec3& v, const double c) {
  return vec3(v.e[0] + c, v.e[1] + c, v.e[2] + c);
};

vec3 operator+(const double c, const vec3& v) {
  return v + c;
};

vec3 operator-(const vec3& v1, const vec3& v2) {
  return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
};

vec3 operator-(const vec3& v, const double c) {
  return vec3(v.e[0] - c, v.e[1] - c, v.e[2] - c);
};

vec3 operator-(const double c, const vec3& v) {
  return v - c;
};

vec3 operator-(const vec3& v1) {
  return -v1;
}
 
vec3 operator*(const vec3& v1, const vec3& v2) {
  return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
};

vec3 operator*(const vec3& v, const double c) {
  return vec3(v.e[0] * c, v.e[1] * c, v.e[2] * c);
};

vec3 operator*(const double c, const vec3& v) {
  return v * c;
};

vec3 operator/(const vec3& v, const double c) {
  return v * (1/c);
};

vec3 operator/(const double& c, const vec3& v) {
  return v / c;
};

double dot(const vec3& v1, const vec3& v2) {
  return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v1.e[2];
};

double vec3::length() const {
  return std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}

double vec3::length_squared() const {
  return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}
vec3 cross(const vec3& u, const vec3& v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], 
      u.e[2] * v.e[0] - u.e[0] * v.e[2],
      u.e[0] * v.e[1] - u.e[1] * v.e[0]
      );
};
vec3 unit(const vec3& v) {
  return v / v.length();
}


