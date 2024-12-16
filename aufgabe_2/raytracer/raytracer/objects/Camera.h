//
// Created by blackrat on 06.11.24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../../math.h"
#include "Screen.h"
#include "Sphere3d.h"

class Camera : Sphere3d {
public:
    Vector3df position{}; //we have this here, as the implementation geometry.h always uses position as a parameter of an object itself
    Vector3df direction{};
    int fov;
    Screen screen;
public:
    Camera() : Camera(60, {0,0,0},{1,0,0}, 1024, 768) {}
    explicit Camera(const int fov) : Camera(fov, {0,0,0},{1,0,0}, 1024, 768) {}
    explicit Camera(const int fov, const Vectorclr position, Vectorclr direction, const int width, const int height): Sphere3d() {
        this->position = position;
        this->direction = direction;
        this->fov = fov;

        direction *= fov;
        Vector3df screenPos = position+direction;
        this->screen = Screen(width, height, {0,0,0}, screenPos); //TODO implement screen placement based on fov value
    }

    std::vector<Ray3df> getInitialRays() const {
        std::vector<Ray3df> rays = {};
        for (auto pixel : screen.getAllPixels()) {
            auto ray = Ray3df(this->position, pixel-this->position);
            rays.insert(rays.end(), ray);
        }
        return rays;
    }

    void trace() {
        auto rays = getInitialRays();

        std::vector<Vectorclr> pixels = screen.getAllPixels();
        for (auto pixel : pixels) {
            //if (pixel.rays.empty()) break;
        }


        //once per pixel
        //go through

        while (!rays.empty()) {
            //we trace each ray here, so that we can see what exactly we do for each ray and can display any change directly on the screen
            for (const Ray3df& ray : rays) {

                //Sphere3d object = findNextObjectCollision(ray);

                //do everything for collision
                //eg. lampertian shading...
                //update current image
                //screen.setPixelColor();
            }

            //work through all collisions
            //create new vector of rays

            //repeat until no new rays are created
        }
    }

    //TODO Change return type to better fit a collision?
    std::vector<Ray3df> tracePrimary(Ray3df ray) {
        //TODO
    }


    // returns if two Cameras are equal
    friend bool operator==(const Camera& lhs, const Camera& rhs);
};

#endif //CAMERA_H
