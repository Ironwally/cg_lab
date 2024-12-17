//
// Created by blackrat on 06.11.24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <optional>

#include "../../math.h"
#include "Screen.h"
#include "../objects/Sphere3d.h"
#include "../objects/Scene.h"
#include "../logic/HitContext.h"

class Camera {
public:
    Screen screen;
    Vector3df center{0,0,0}; //we have this here, as the implementation geometry.h always uses center (position) as a parameter of an object itself
    Vector3df gap_u{0,0,0};
    Vector3df gap_v{0,0,0};
    Vector3df pixel00_location{0,0,0};
    int max_depth;

public:
    Camera(const Screen screen) : Camera(screen, 60, 10) {}
    explicit Camera(const Screen screen, const int fov, const int max_depth) : Camera(screen, fov, max_depth, {0,0,0},{-0.4,0.2,0.7}, 1024, 768) {}
    explicit Camera(const Screen screen, const int fov, const int max_depth, const Vectorclr position, Vectorclr camera_direction, const int width, const int height): screen(
        screen) {
        this->center = position;
        this->max_depth = max_depth;
        this->screen = screen;

        // TODO fix camera direction

        // TODO Calculate viewport size based on field of view (fov)
        // Calculate the height of the viewport based on the screen's aspect ratio
        const auto viewportHeight = static_cast<float>(2.0f * (static_cast<double>(screen.height) /
            screen.width));

        // Define the horizontal and vertical vectors for the viewport
        const Vector3df viewportU = {2.0f, 0.0f, 0.0f};
        const Vector3df viewportV = {0.0f, -viewportHeight, 0.0f};

        // Calculate the gap between pixels in the horizontal and vertical directions
        this->gap_u = 1.0f / static_cast<float>(screen.width) * viewportU;
        this->gap_v = 1.0f / static_cast<float>(screen.height) * viewportV;

        // Calculate position of the most upper-left pixel
        //camera_direction.normalize();
        const Vector3df viewportUpperLeft = center - camera_direction - 0.5f * viewportU - 0.5f * viewportV;
        this->pixel00_location = viewportUpperLeft + 0.5f * (gap_u + gap_v);
    }

    void trace(const Scene scene) {
        std::vector<Vectorclr> pixels = screen.getAllPixels();
        for (size_t i = 0; i < pixels.size(); ++i) {
            const int x = i%screen.width;
            const int y = i/screen.width;
            const Ray3df initial_ray = get_initial_Ray(x, y);
            const auto pixel = traceRay(initial_ray, scene, max_depth);
            screen.setPixelColor(pixel, i);
        }

        //once per pixel
        //go through
        /*
        while (!rays.empty()) {
            //we trace each ray here, so that we can see what exactly we do for each ray and can display any change directly on the screen
            for (Ray3df& ray : rays) {

                //Sphere3d object = findNextObjectCollision(ray);

                //do everything for collision
                //eg. lambertian shading...
                //update current image
                //screen.setPixelColor();
            }

            //work through all collisions
            //create new vector of rays

            //repeat until no new rays are created
        }
        */
    }

private:
    Ray3df get_initial_Ray(const int x, const int y) {
        auto abstand_u = gap_u;
        abstand_u *= x;
        auto abstand_v = gap_v;
        abstand_v *= y;
        const auto pixel_pos = pixel00_location + abstand_u + abstand_v;
        const auto ray_direction = pixel_pos - center;
        return Ray3df(center, ray_direction);
    }

    Vectorclr traceRay(const Ray3df ray, const Scene& scene, int recursion_depth) {
        Vectorclr color = BLACK;
        if (std::optional<HitContext> opt_hit = find_next_hit(ray, scene); opt_hit.has_value() && recursion_depth>0) {
            HitContext hit = opt_hit.value();
            if (hit.get_sphere3d().get_material().get_reflective()) {
                //derzeit komplette Reflektion oder gar keine
                //Schattenakne korrektur
                auto [u, v, t, normal, intersection] = hit.get_intersection_context();
                const Vector3df corrected_ray_origin = intersection + 1e-4f * normal;
                Vector3df reflected_direction = ray.direction - 2 * (ray.direction * normal) * normal;
                const Ray3df reflected_ray(corrected_ray_origin, reflected_direction);
                color = traceRay(reflected_ray, scene, recursion_depth-1);
            } else {
                /*
                std:std::vector<Vector3df> lights;
                if (!traceShadows(hit, scene)) {
                    lights.push_back(scene.get_lightSource());
                };
                */
                color = lambertianShading(hit, scene);
            }
        }
        return color;
    }

    bool traceShadows(HitContext& hit, const Scene& scene) {
        Ray3df shadow_ray(hit.get_intersection_context().intersection, scene.get_lightSource()-hit.get_intersection_context().intersection);

        if (std::optional<HitContext> context = find_next_hit(shadow_ray, scene); context.has_value()) {
            HitContext shadow_context = context.value();
            //...
            return true;
        } // TODO find nicer way of checking for null than optional ... if()
        else {
            return false;
        }

    }

    Vectorclr lambertianShading(HitContext hit, Scene scene) {
        Vectorclr color = BLACK;
        Vector3df lightDir = (scene.get_lightSource() - hit.get_intersection_context().intersection);
        lightDir.normalize();
        // compute lambertian reflectance with minimum of 0.3
        float intensity_lambertian = std::max(hit.get_intersection_context().normal * lightDir, 0.3f);
        //if (traceShadows(hit, scene)) {
        //    intensity_lambertian = 0.3f;
        //}
        color = hit.get_sphere3d().get_material().get_diffuseColor();
        // scale color by lambertian reflectance to account for diffuse reflection
        color *= intensity_lambertian;
        return color;
    }

    std::optional<HitContext> find_next_hit(Ray3df ray, Scene scene) {
        Intersection_Context<float, 3> context;
        float minimal_t =std::numeric_limits<float>::max();
        std::optional<HitContext> hit;

        for (auto& sphere : scene.get_objects()) {
            if (sphere.intersects(ray, context) && context.t > 0 && context.t < minimal_t) {
                minimal_t = context.t;
                hit = HitContext(sphere, context);
            }

        }
        return hit;
    }

    //TODO Change return type to better fit a collision?
    HitContext tracePrimary(Ray3df ray) {
        //TODO
    }


    // returns if two Cameras are equal
    friend bool operator==(const Camera& lhs, const Camera& rhs);
};

#endif //CAMERA_H
