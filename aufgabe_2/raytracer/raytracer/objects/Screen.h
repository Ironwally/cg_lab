//
// Created by blackrat on 31.10.24.
//
#ifndef BILDSCHIRM_H
#define BILDSCHIRM_H


#include "../../geometry.h"
#include "../../math.h"
#include "../configuration/configuration.h"


class Screen {
private:
    //Vector3df left,right,bottom,top;
    std::vector<Vectorclr> pixels;
    //Vector<Vectorclr, WIDTH * HEIGHT> pixels = {}; //include = {}? // old
public:
    int width;
    int height;
    int length;
    Screen() : Screen(1024,768,{0,0,0}) {}
    Screen(const int width, const int height) : Screen(width, height, {0,0,0}) {}
    explicit Screen(const int width, const int height, const Vectorclr start_color) {
        this->width = width;
        this->height = height;
        this->length = width*height;
        this->pixels = {};
        for (int i = 0; i < length; i++) {
            pixels.insert(pixels.end(),start_color);
        }
    }
    void setPixelColor(Vectorclr color, const int x, const int y) {
        pixels[x + y * height] = color;
    }
    [[nodiscard]] Vectorclr getPixelColor(const int x, const int y) const
    {
        return pixels[x + y * height];
    }

    [[nodiscard]] std::vector<Vectorclr> getAllPixels() const {
        return pixels;
    }
    // returns if two Screens are equal
    template <size_t F, size_t K>
    friend bool operator==(const Screen& lhs, const Screen& rhs);
};



#endif //BILDSCHIRM_H
