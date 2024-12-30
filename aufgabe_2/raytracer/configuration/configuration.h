//
// Created by blackrat on 31.10.24.
//

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../../math.h"

const int AMOUNT_RAYS = 10;
const int MAX_RAY_RECURSION_DEPTH = 2;

// Color vector
typedef Vector3df Vectorclr;

// Color constants
const Vectorclr RED{255, 0, 0};
const Vectorclr GREEN{0, 255, 0};
const Vectorclr BLUE{0, 0, 255};
const Vectorclr WHITE{255, 255, 255};
const Vectorclr BLACK{0, 0, 0};
const Vectorclr YELLOW{255, 255, 0};
const Vectorclr ORANGE{255, 165, 0};

#endif //CONFIGURATION_H
