#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
  public:
    double radius;
    point3 center; 
    shared_ptr<material> mat;

    sphere(const point3& center, double radius, shared_ptr<material> mat) 
      : radius(std::fmax(0, radius)), mat(mat), center(center) {};

    bool hit(const ray& r, interval ray_t, hit_record& rec) override {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = h*h - a*c;

        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        auto root = (h - sqrtd) / a; 

        // check (-b + sqrt(discriminant)) / 2*a and (-b - sqrt(discriminant)) / 2*a to see if any of them  
        // are within bounds.
        if (!ray_t.surrounds(root)) {
          root = (h + sqrtd) / a;
          if (!ray_t.surrounds(root)) {
            return false;
          }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true; 
    }

    point3 get_center() override {
      return center;
    }

    point3 get_max() override {
      point3 max_point(-infinity, -infinity, -infinity);

      max_point.e[0] = fmaxf(max_point.e[0], center.x() + radius);
      max_point.e[1] = fmaxf(max_point.e[1], center.y() + radius);
      max_point.e[2] = fmaxf(max_point.e[2], center.z() + radius);

      return max_point;
    }
    
   point3 get_min() override {
      point3 min_point(infinity, infinity, infinity);

      min_point.e[0] = fminf(min_point.e[0], center.x() - radius);
      min_point.e[1] = fminf(min_point.e[1], center.y() - radius);
      min_point.e[2] = fminf(min_point.e[2], center.z() - radius);

      return min_point;
    }

};

#endif // !SPHERE_H
