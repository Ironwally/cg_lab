//
// Created by marti on 16.12.2024.
//

#ifndef SCENE_H
#define SCENE_H
#include "Sphere3d.h"
#include "../math/math.h"
#include "../configuration/configuration.h"


// Scene objects and light
class Scene {
    Vector3df lightSource = {0,0,0};
    std::vector<Sphere3d> objects;

    void generateScene() {
        // Konstanten
        const Vector3df leftWallPos = {-1000010, 0, 0};
        const Vector3df rightWallPos = {1000010, 0, 0};
        const Vector3df floorPos = {0, -1000010, 0};
        const Vector3df ceilingPos = {0, 1000010, 0};
        const Vector3df backPos = {0, 0, -1000050};
        const Vector3df frontPos = {0, 0, 1000000};
        constexpr float bigRadius = 1000000;
        constexpr float regRadius = 3;
        // Walls
        objects.push_back(Sphere3d(Sphere3df(leftWallPos, bigRadius), Material(RED, false)));
        objects.push_back(Sphere3d(Sphere3df(rightWallPos, bigRadius), Material(GREEN, false)));
        objects.push_back(Sphere3d(Sphere3df(floorPos, bigRadius), Material(WHITE, false)));
        objects.push_back(Sphere3d(Sphere3df(ceilingPos, bigRadius), Material(WHITE, false)));
        objects.push_back(Sphere3d(Sphere3df(backPos, bigRadius), Material(WHITE, false)));
        objects.push_back(Sphere3d(Sphere3df(frontPos, bigRadius), Material(BLACK, false)));
        // Spheres
        objects.push_back(Sphere3d(Sphere3df({-6, -7, -25}, 3), Material(YELLOW, false)));
        objects.push_back(Sphere3d(Sphere3df({6, -7, -25}, 4), Material(ORANGE, true)));
        objects.push_back(Sphere3d(Sphere3df({0, -7, -40}, 2), Material(BLUE, false)));
        objects.push_back(Sphere3d(Sphere3df({-4, 3, -30}, 4), Material(BLUE, true)));
        // LightSources
        lightSource = {0, 9, -18};
    }

public:
    Scene() {
        generateScene();
    }

    Vector3df get_lightSource() const {
        return lightSource;
    }

    std::vector<Sphere3d> get_objects() const {
        return objects;
    }
};



#endif //SCENE_H
