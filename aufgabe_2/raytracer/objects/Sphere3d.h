//
// Created by blackrat on 07.11.24.
//

#ifndef SPHERE3D_H
#define SPHERE3D_H
#include "Material.h"
#include "../geometry/geometry.h"
#include "../configuration/configuration.h"

class Sphere3d{
    Sphere3df shape;
    Material material;
public:
    Sphere3d() : Sphere3d(Sphere3df({0,0,0},0), Material({0,0,0},0)){}
    Sphere3d(const Sphere3df& sphere, const Material& mat) : shape(sphere), material(mat) {
    }

    bool intersects(const Ray3df& ray, Intersection_Context<float, 3>& context) const {
        return shape.intersects(ray, context);
    }

    [[nodiscard]] Sphere3df get_shape() const {
        return shape;
    }

    [[nodiscard]] Material get_material() const {
        return material;
    }

};

#endif //SPHERE3D_H
