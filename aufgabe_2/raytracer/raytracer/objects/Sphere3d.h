//
// Created by blackrat on 07.11.24.
//

#ifndef SPHERE3D_H
#define SPHERE3D_H
#include "Material.h"
#include "../../geometry.h"
#include "../configuration/configuration.h"
#include "../objects/Object3d.h"

class Sphere3d : public Object3d {
    Sphere3df shape;
    Material material;
public:
    Sphere3d(const Sphere3df& sphere, const Material& mat) : Object3d(), shape(sphere), material(mat) {

    }

    bool intersects(const Ray3df& ray, Intersection_Context<float, 3>& context) const {
        return shape.intersects(ray, context);
    }
};

#endif //SPHERE3D_H
