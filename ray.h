#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
private:
    point3 origin;
    vec3 direction;

public:
    ray() {}
    ray(const point3& orig, const point3& dir)
        : origin(orig), direction(dir) {}
    
    const point3& Origin() const { return origin; }
    const point3& Direction() const { return direction; }

    point3 At(double t) const { return origin + direction*t; }
};

#endif /* ray.h */