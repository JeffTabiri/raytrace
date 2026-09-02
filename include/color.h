#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <vec3.h>

class color {
  public:
    double e[3];

    color() : e {0,0,0} {};
    color(double e0, double e1, double e2) : e {e0, e1, e2} {};

    double x() const { return e[0];}
    double y() const { return e[1];}
    double z() const { return e[2];}
    double length() const;
};
    
std::ostream& operator<<(std::ostream& out, const color& v); 

color operator+(const color& v1, const color& v2);
color operator+(const color& v, const double c);
color operator+(const double c, const color& v);
color operator+(const vec3 v, const color& c);
color operator+(const color& c, const vec3& v);

color operator-(const color& v1, const color& v2);
color operator-(const color& v, const double c); 
color operator-(const double c, const color& v);
color operator-(const vec3 v, const color& c);
color operator-(const color& c, const vec3& v);
 
color operator*(const color& v1, const color& v2);
color operator*(const color& v, const double c);
color operator*(const double c, const color& v);
color operator*(const vec3 v, const color& c);
color operator*(const color& c, const vec3& v);

color operator/(const color& v, const double c);
color operator/(const double& c, const color& v);

void write_color(std::ostream& out, const color& v); 

#endif 
