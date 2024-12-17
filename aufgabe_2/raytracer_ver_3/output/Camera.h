//
// Created by marti on 16.12.2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../geometry/geometry.h"
#include "../math/math.h"

class Camera {

public:
  std::vector<VectorColor>& pixels;
  double aspect_ratio = 1.0;
  int width = 100;
  int samples_per_pixel = 10;
  int max_depth = 10;

  Vector3df lookfrom = Vector3df{0,0,0};
  Vector3df lookat = Vector3df{0,0,-1};
  Vector3df vup = Vector3df{0,1,0}; // Camera-relativ "up" direction

  double focus_dist = 10;

  Camera() {
    this->aspect_ratio = 16.0 / 9.0;
    this->width = 1200;
    this->samples_per_pixel = 10;
    this->max_depth = 20;

    this.vfov     = 20;
    this->lookfrom = point3(13,2,3);
    this->lookat   = point3(0,0,0);
    this->vup      = Vector3df{0,1,0};
    }

  void render(const hittable& scene) {
    initialize();
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    // render per pixel
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        Ray ray = get_ray(x,y);
        VectorColor color = trace(ray, scene, max_depth-1);
        setPixel(x,y, color);
      }
    }
    std::clog << "\rDone.                 \n";
  }
  VectorColor trace(const Ray3df ray, const hittable& scene, int max_depth) {
    Hitcontext hit = find_next_object(ray, scene);
    VectorColor color = BACKGROUND_COLOR;
    Light [] lights;
    if (hit != NULL) {
      lights = scene.find_light_sources(hit_context);
      n = scene.get_lights().size();
      color = lambertian(n, lights, hit);
      if (hit.object.reflective) {
        // TODO
      }
    }
    return color;
  }

private:
  int height;
  Vector3df center;
  Vector3df pixel00_location;
  Vector3df pixel_delta_u;        // Offset to pixel to the right
  Vector3df pixel_delta_v;        // Offset to pixel below
  Vector3df u, v, w;              // Camera frame basis vectors
  double pixel_samples_scale;  // Color scale factor for a sum of pixel samples

  void setPixel(int x,int y, VectorColor color) {
    pixels[y * width + x] = color;
  }

  Light[] find_light_sources(HitContext hit_context) {
    Light[] visible_lights;
    for (Light light : lights) {
      Ray3df shadow_ray(hit_context.intersection,
                          light.position - hit_context.intersection);
      HitContext shadow_context = scene.find_nearest_object(shadow_ray);
      if (shadow_context == NULL) {
        visible_lights.add(light);
      }
    }
    return visible_lights;
  }

  void initialize() {
    height = int(width / aspect_ratio);
    height = (height < 1) ? 1 : height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = lookfrom;

    auto h = std::tan(20/2);
    auto viewport_height = 2 * h * focus_dist;
    auto viewport_width = viewport_height * (double(width)/height);

    // Calculate u,v,w for camera coordinate frame.
    w = (lookfrom - lookat);
    w.normalize();
    u = vup.cross_product(w);
    u.normalize();
    v = w.cross_product(u);

    // lambda for nicer syntax
    auto multiply = [](Vector3df v, float v2) -> Vector3df { Vector3df val = v; val *= v2; return val; };
    auto divide = [](Vector3df v, float v2) -> Vector3df { Vector3df val = v; val /= v2; return val; };

    Vector3df viewport_u = multiply(u, viewport_width);
    Vector3df viewport_v = multiply(-v, viewport_height);

    // horizontale, vertikale Viewport-Kanten Vektoren
    pixel_delta_u = multiply(u, viewport_width);
    pixel_delta_u /= width;
    pixel_delta_v = multiply(v, viewport_height);
    pixel_delta_v /= height;

    // Position des oberen linken Pixels
    auto viewport_upper_left = center - multiply(w, focus_dist) - divide(viewport_v,2) - divide(viewport_u,2);
    pixel00_location = viewport_upper_left - multiply((pixel_delta_u + pixel_delta_v), 0.5);
  }

  Ray3df get_ray(int x, int y) {
    // TODO
  }

};



#endif //CAMERA_H
