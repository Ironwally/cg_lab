//
// Created by blackrat on 31.10.24.
//
#ifndef BILDSCHIRM_H
#define BILDSCHIRM_H


#include "../../geometry.h"
#include "../../math.h"

template<int WIDTH, int HEIGHT>
class Screen {
    Vector<Vector<unsigned char, 3>, WIDTH * HEIGHT> screen; //include = {}?
public:
    Screen() : screen(WIDTH * HEIGHT, {0,0,0}) {}
    explicit Screen(Vector<unsigned char, 3> start_color) {
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            screen[i] = start_color;
        }
    }
    void setColor(Vector3df color, const int x, const int y) {
        screen[x + y * HEIGHT] = color;
    }
};



#endif //BILDSCHIRM_H
