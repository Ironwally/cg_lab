//
// Created by marti on 16.12.2024.
//

#ifndef HITCONTEXT_H
#define HITCONTEXT_H
#include "../objects/Sphere3d.h"


class HitContext {
    Sphere3d sphere3d_;
    Intersection_Context<float, 3> intersection_context_;
public:
    HitContext(Sphere3d& sphere3d, Intersection_Context<float, 3>& intersection_context):
        sphere3d_(sphere3d),intersection_context_(intersection_context)
    {}
    Sphere3d get_sphere3d() {
        return sphere3d_;
    }
    Intersection_Context<float, 3> get_intersection_context() {
        return intersection_context_;
    }
};



#endif //HITCONTEXT_H
