#ifndef MATTER_H
#define MATTER_H

#include "primaryheader.h"
class material;

struct hit_record {
    point3 hit_point;
    vec3 normal;
    double t;
    std::shared_ptr<material> mat;
};

class matter {
  public:
    virtual ~matter() = default;

    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif /* matter.h */