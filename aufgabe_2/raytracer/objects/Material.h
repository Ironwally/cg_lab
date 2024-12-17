//
// Created by blackrat on 07.11.24.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "../../math.h"

class Material {
    Vectorclr diffuseColor;
    bool reflective;
public:
    Material(const Vector3df& diff, const bool ref):
        diffuseColor(diff),
        reflective(ref)
        {}
    Vectorclr get_diffuseColor() {
        return diffuseColor;
    }
    bool get_reflective() {
        return reflective;
    }
};

#endif //MATERIAL_H
