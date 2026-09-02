#ifndef VEC3_H
#define VEC3_H

#include <ostream>

class vec3 {
  public:
    double e[3];
    vec3() : e {0,0,0} {};
    vec3(double e0, double e1, double e2) : e {e0, e1, e2} {};
    double x() const { return e[0];}
    double y() const { return e[1];}
    double z() const { return e[2];}
    double length() const;
    double length_squared() const;
};
    
std::ostream& operator<<(std::ostream& out, const vec3& v); 

vec3 operator+(const vec3& v1, const vec3& v2);
vec3 operator+(const vec3& v, const double c);
vec3 operator+(const double c, const vec3& v);

vec3 operator-(const vec3& v1, const vec3& v2);
vec3 operator-(const vec3& v, const double c); 
vec3 operator-(const double c, const vec3& v);
vec3 operator-(const vec3& v1);
 
vec3 operator*(const vec3& v1, const vec3& v2);
vec3 operator*(const vec3& v, const double c);
vec3 operator*(const double c, const vec3& v);

vec3 operator/(const vec3& v, const double c);
vec3 operator/(const double& c, const vec3& v);

double dot(const vec3& v1, const vec3& v2);
vec3 cross(const vec3& u, const vec3& v);
vec3 unit(const vec3& v);
#endif // !VEC_H
