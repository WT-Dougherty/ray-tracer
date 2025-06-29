#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

inline double clamp(double x) {
    if (x < 0) return 0;
    if (x > 0.999) return 0.999;
    return x;
}

inline void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.X();
    auto g = pixel_color.Y();
    auto b = pixel_color.Z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(256 * clamp(r));
    int gbyte = int(256 * clamp(g));
    int bbyte = int(256 * clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif