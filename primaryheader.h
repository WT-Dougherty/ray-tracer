#ifndef PRIMARYHEADER_H
#define PRIMARYHEADER_H

// libraries
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

// headers
#include "color.h"
#include "ray.h"
#include "vec3.h"

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589793238462643383279;

// conversion function
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

#endif /* primaryheader.h */