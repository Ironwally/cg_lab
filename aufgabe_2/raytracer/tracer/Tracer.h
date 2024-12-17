//
// Created by blackrat on 31.10.24.
//

#ifndef TRACER_H
#define TRACER_H

#include "../../raytracer/configuration/configuration.h"
#include "../renderer/Screen.h"
#include "../renderer/Camera.h"

class Tracer {
public:
    //Screen screen;
    Camera camera;
    std::vector<Sphere3d> objects;

public:
    Tracer(const Screen& screen, const Camera& camera, const std::vector<Sphere3d>& objects): camera(camera) {
        //this->screen = screen;
        this->camera = camera;
        this->objects = objects;
    }

    void tracePrimary(const Screen* screen)
    {
        const auto pixels = screen->getAllPixels();
        constexpr auto length = sizeof(pixels)/sizeof(pixels[0]);
        for (unsigned long long i=0;i<length;i++) {
            const auto ray = Ray3df(camera.center, pixels[i]-camera.center);
            this->tracePrimary_single(ray);
        }
        std::vector<Ray3df> rays = {};
        for (const auto pixel : screen->getAllPixels()) {
            auto ray = Ray3df(camera.center, pixel-camera.center);
            rays.insert(rays.end(), ray);
            this->tracePrimary_single(ray);
        }
    }
    void tracePrimary_single(Ray3df ray) {
        //TODO
    }
};


#endif //TRACER_H
