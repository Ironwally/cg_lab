//
// Created by blackrat on 07.11.24.
//

#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H
#include "Material.h"
#include "../../geometry.h"

class Triangle3d : public Object3d {
    Triangle3df shape;
    Material material;

    Triangle3d(const Triangle3df& shape, const Material& mat) : shape(shape), material(mat) {}

    bool intersects(const Ray3df& ray, Intersection_Context<float, 3>& context) const {
        return shape.intersects(ray, context);
    }

    int getSize() {
        //TODO
    }
};

#endif //TRIANGLE3D_H
