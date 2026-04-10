#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray
{
private:
    Point3 origin;
    Vec3 direction;

public:
    Ray() {}
    Ray(const Point3 &orig, const Point3 &dir)
        : origin(orig), direction(dir) {}

    const Point3 &getOrigin() const { return origin; }
    const Vec3 &getDirection() const { return direction; }

    Point3 at(double t) const { return origin + direction * t; }
};

#endif /* ray.h */
