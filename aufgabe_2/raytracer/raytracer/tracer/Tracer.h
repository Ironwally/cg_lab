//
// Created by blackrat on 31.10.24.
//

#ifndef TRACER_H
#define TRACER_H

#include "../../raytracer/configuration/configuration.h"
#include "../../raytracer/screen/Screen.h"
#include "../../raytracer/objects/Camera.h"
#include "../objects/Object3d.h"

class Tracer {
public:
    //Screen screen;
    Camera camera;
    std::vector<Sphere3d> objects;

public:
    Tracer(/*const Screen& screen,*/const Camera& camera, const std::vector<Sphere3d>& objects) {
        //this->screen = screen;
        this->camera = camera;
        this->objects = objects;
    }

    void tracePrimary(const Screen* screen)
    {
        const auto pixels = screen->getAllPixels();
        constexpr auto length = sizeof(pixels)/sizeof(pixels[0]);
        for (auto i=0;i<length;i++) {
            const auto ray = Ray3df(camera.position, pixels[i]-camera.position);
            this->tracePrimary_single(ray);
        }
        std::vector<Ray3df> rays = {};
        for (const auto pixel : screen->getAllPixels()) {
            auto ray = Ray3df(camera.position, pixel-camera.position);
            rays.insert(rays.end(), ray);
            this->tracePrimary_single(ray);
        }
    }
    void tracePrimary_single(Ray3df ray) {
        //TODO
    }
};


#endif //TRACER_H
