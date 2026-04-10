#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include <iostream>

using Color = Vec3;

inline double clamp(double x)
{
    if (x < 0)
        return 0;
    if (x > 0.999)
        return 0.999;
    return x;
}
inline double linearToGamma(double linearComponent)
{
    if (linearComponent > 0)
        return std::sqrt(linearComponent);

    return 0;
}

inline void writeColor(std::ostream &out, const Color &pixelColor)
{
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(256 * clamp(r));
    int gbyte = int(256 * clamp(g));
    int bbyte = int(256 * clamp(b));

    // Apply gamma correction.
    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
