#include "raytracer/objects/Screen.h"
#include "gtest/gtest.h"
#include "raytracer/objects/Camera.h"
#include "raytracer/configuration/configuration.h"
#include "raytracer/objects/Sphere3d.h"
#include "raytracer/objects/Triangle3d.h"
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

    TEST(OBJECTS, sphere_intersects_itself) {
        auto sphere = Sphere3d(Sphere3df({0,0,0},5), Material({0,0,0},{0,0,0},{0,0,0},1));
        //EXPECT_EQ(true, sphere.intersects({{0,0,0},{1,0,0}},{}));
    }
    //Triangle only if sphere works perfectly
    /*
    TEST(OBJECTS, create_wall) {
        auto wall = Triangle3d(2,5,1, {0,0,1});
        EXPECT_EQ({0,0,1}, wall.getPos());
        EXPECT_EQ(2 , wall.getSize()[0]);
    }
    */
}
