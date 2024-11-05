#include "raytracer/screen/Screen.h"
#include "gtest/gtest.h"

namespace {
    TEST(SCREEN, CREATE_SCREEN) {
        auto screen = Screen<1024, 768>();
        screen.setColor({1,1,1}, 0,0);

        EXPECT_EQ({1,1,1}, screen[0], 0.00001);
    }

}
