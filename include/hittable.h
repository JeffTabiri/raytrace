#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"

class material;

class hit_record {
  public:
    point3 p; 
    vec3 normal;
    double t;
    shared_ptr<material> mat;
    bool front_face;
    bool hit_anything;
    float closest_so_far;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
      front_face = dot(r.direction(), outward_normal) < 0;
      normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) = 0;
    virtual point3 get_center() = 0;
    virtual point3 get_min() = 0;
    virtual point3 get_max() = 0;
};

#endif

