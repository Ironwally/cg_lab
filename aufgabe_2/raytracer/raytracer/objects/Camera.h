//
// Created by blackrat on 06.11.24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../../math.h"
#include "../objects/Screen.h"

class Camera {
public:
    Vector3df position{}; //TODO put position in cornellbox
    Vector3df direction{};
    int fov;
public:
    Camera() : Camera(60, {0,0,0},{1,0,0}) {}
    explicit Camera(const int fov) : Camera(fov, {0,0,0},{1,0,0}) {}
    explicit Camera(const int fov, const Vectorclr position, const Vectorclr direction) {
        this->position = position;
        this->direction = direction;
        this->fov = fov;
    }

    /*
    [[nodiscard]] std::vector<Ray3df> getRays(const Screen* screen) const {
        std::vector<Ray3df> rays = {};
        for (auto pixel : screen->getAllPixels()) {
            auto ray = Ray3df(this->position, pixel-this->position);
            rays.insert(rays.end(), ray);
        }
        return rays;
    }
    */

    // returns if two Cameras are equal
    friend bool operator==(const Camera& lhs, const Camera& rhs);
};

#endif //CAMERA_H
