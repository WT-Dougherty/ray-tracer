#ifndef SPHERE_H
#define SPHERE_H

#include "matter.h"
#include "vec3.h"

class sphere : public matter {
private:
    point3 center;
    double radius;
    std::shared_ptr<material> mat;
public:
    sphere(point3 c, double r, std::shared_ptr<material> m)
        : center(c), radius(r), mat(m) {}
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override;
};

#endif /* sphere.h */