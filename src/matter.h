#ifndef MATTER_H
#define MATTER_H

#include "primaryheader.h"
class Material;

struct HitRecord
{
  Point3 hitPoint;
  Vec3 normal;
  double t;
  std::shared_ptr<Material> mat;
};

class Matter
{
public:
  virtual ~Matter() = default;

  virtual bool hit(const Ray &r, double rayTmin, double rayTmax, HitRecord &rec) const = 0;
};

#endif /* matter.h */
