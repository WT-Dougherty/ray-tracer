#include "sphere.h"
#include "math.h"

bool Sphere ::hit(const Ray &r, double rayTmin, double rayTmax, HitRecord &rec) const
{
    // init vars
    Vec3 cmo = center - r.getOrigin();
    auto a = r.getDirection().lenSquared();
    auto b = -2.0 * (r.getDirection() * cmo);
    auto c = cmo.lenSquared() - (radius * radius);
    auto discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0)
    {
        return false;
    }

    // there has been a hit
    auto t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (t < rayTmin || t > rayTmax)
    {
        t = (-b + std::sqrt(discriminant)) / (2.0 * a);
        if (t < rayTmin || t > rayTmax)
        {
            return false;
        }
    }

    // update hit record
    rec.hitPoint = r.at(t);
    rec.normal = (r.at(t) - center) / radius;
    rec.t = t;
    rec.mat = mat.get();
    return true;
}
