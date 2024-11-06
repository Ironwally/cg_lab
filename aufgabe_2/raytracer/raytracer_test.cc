#include "raytracer/screen/Screen.h"
#include "gtest/gtest.h"
#include "raytracer/objects/Camera.h"
#include "raytracer/configuration/configuration.h"
#include "raytracer/tracer/Tracer.h"

namespace {
    TEST(SCREEN, set_pixel_color) {
        auto screen = Screen(1024, 768);
        screen.setPixelColor({1,1,1}, 0,0);
        const Vectorclr shouldbe = {1,1,1};
        EXPECT_EQ(shouldbe, screen.getPixelColor(0,0));
        const bool test = shouldbe == screen.getPixelColor(0,0); //implemented operator==
        EXPECT_EQ(true, test);
    }
    /*
    * TODO: fix: no match for operator== (Screen)
    TEST(TRACER, create_tracer) {
        auto screen = Screen(1024, 768);
        screen.setPixelColor({1,1,1}, 0,0);
        const auto camera = Camera();
        const auto tracer = Tracer(screen, camera);

        EXPECT_EQ(tracer.screen, screen);
        EXPECT_EQ(tracer.camera, camera);
    }
    */

    TEST(OBJECTS, create_sphere) {
        Sphere3d sphere = Sphere3d(5, {0,0,1});
        EXPECT_EQ(5, sphere.radius);
    }
    TEST(OBJECTS, create_wall) {
        Wall3d wall = Wall3d(2,5,1, {0,0,1});
        EXPECT_EQ({0,0,1}, wall.getPos());
        EXPECT_EQ(2 , wall.getSizeX());
    }
}
