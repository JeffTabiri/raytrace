#include "color.h"
#include "constants.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ostream>

constexpr int max_color = 255;
typedef vec3 point3;

color ray_color(const ray& r, const hittable& world) {
  hit_record rec;

  if (world.hit(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + color(1,1,1));
  }

  vec3 unit_direction = unit(r.direction());
  float a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main (int argc, char *argv[]) {

  // Image 
  float aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  int image_height = int(image_width / aspect_ratio);
  image_height = std::max(1, image_height);

  // world
  hittable_list world;
  world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
  world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100));

  // Camera
  
  // distance between camera center and the viewport
  float focal_length = 1.0;
  float viewport_height = 2.0;
  float viewport_width = viewport_height * (double(image_width) / image_height);
  // a point in space from which scene rays will originate from
  point3 camera_center = point3(0,0,0);

  // Calculate the vectors across horizontal and down the vertical edges.
  vec3 viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  vec3 pixel_delta_u = viewport_u / image_width; 
  vec3 pixel_delta_v = viewport_v / image_height;

  // calculate the location of upper left pixel
  auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 -viewport_v/2;
  auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // render 
  std::cout << "P3";
  std::cout << "\n";
  
  std::cout << image_width;
  std::cout << " ";
  std::cout << image_height;
  std::cout << "\n";

  std::cout << max_color;
  std::cout << "\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << '\n' << std::flush;
    for (int i = 0; i < image_width; i++) {
      auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);

      // direction from the camera center to pixel center.
      auto ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);

      color pixel_color = ray_color(r, world);
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\rDone.               \n";

  return 0;
}
