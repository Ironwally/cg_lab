//
// Created by marti on 16.12.2024.
//

#ifndef SPHERE3D_H
#define SPHERE3D_H

#include "Material.h"
#include "../geometry/geometry.h"

class Sphere3d {
    Sphere3df shape;
    Material material;
public:
    Sphere3d() : Sphere3d(Sphere3df({0,0,0},0), Material({0,0,0},{0,0,0},{0,0,0},0)){}
    Sphere3d(const Sphere3df& sphere, const Material& mat) : shape(sphere), material(mat) {
    }

    bool intersects(const Ray3df& ray, Intersection_Context<float, 3>& context) const {
        return shape.intersects(ray, context);
    }
};



#endif //SPHERE3D_H
