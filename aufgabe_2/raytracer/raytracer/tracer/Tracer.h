//
// Created by blackrat on 31.10.24.
//

#ifndef TRACER_H
#define TRACER_H

#include "../../raytracer/configuration/configuration.h"
#include "../../raytracer/screen/Screen.h"
#include "../../raytracer/objects/Camera.h"

class Tracer {
public:
    Screen screen;
    Camera camera;
public:
    Tracer(const Screen screen, const Camera camera) {
        this->screen = screen;
        this->camera = camera;
    }
    void tracePrimary()
    {
        auto pixels = this->screen.getAllPixels();
        const auto length = sizeof(pixels)/sizeof(pixels[0]);
        for (auto i=0;i<length;i++) {
            this->tracePrimary_single(pixels[i]);
        }
    }
    void tracePrimary_single(Vectorclr pixel) {
        //TODO
    }
};


#endif //TRACER_H
