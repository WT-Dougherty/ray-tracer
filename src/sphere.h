#ifndef SPHERE_H
#define SPHERE_H

#include "matter.h"
#include "vec3.h"

class Sphere : public Matter
{
private:
    Point3 center;
    double radius;
    std::shared_ptr<Material> mat;

public:
    Sphere(Point3 c, double r, std::shared_ptr<Material> m)
        : center(c), radius(r), mat(m) {}
    bool hit(const Ray &r, double rayTmin, double rayTmax, HitRecord &rec) const override;
};

#endif /* sphere.h */
