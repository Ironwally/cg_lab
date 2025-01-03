//
// Created by marti on 16.12.2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "../math/math.h"


class Material {
    Vector3df ambient, diffuse, specular;
    float reflective;
public:
    Material(const Vector3df& amb, const Vector3df& diff, const Vector3df& spec, const float ref) :
    ambient(amb),
    diffuse(diff),
    specular(spec),
    reflective(ref)
    {}

};



#endif //MATERIAL_H
