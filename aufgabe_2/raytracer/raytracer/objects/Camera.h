//
// Created by blackrat on 06.11.24.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "../../math.h"
#include "../screen/Screen.h"

class Camera
{
private:
    Vectorclr position{};
    Vectorclr direction{};
public:
    Camera() : Camera({0,0,0},{1,0,0}) {}
    explicit Camera(const Vectorclr position, const Vectorclr direction) {
        this->position = position;
        this->direction = direction;
    }
    // returns if two Cameras are equal
    friend bool operator==(const Camera& lhs, const Camera& rhs);
};

#endif //CAMERA_H
