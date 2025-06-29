#include "sphere.h"
#include "math.h"

bool sphere :: hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const
{
    // init vars
    vec3 cmo = center - r.Origin();
    auto a = r.Direction().len_squared();
    auto b = -2.0 * ( r.Direction() * cmo );
    auto c = cmo.len_squared() - ( radius*radius );
    auto discriminant = b*b - 4.0*a*c;
    if ( discriminant < 0 ) { return false; }
    
    // there has been a hit
    auto t = ( -b - std::sqrt(discriminant) ) / (2.0 * a);
    if ( t < ray_tmin || t > ray_tmax ) {
        t = ( -b + std::sqrt(discriminant) ) / (2.0 * a);
        if ( t < ray_tmin || t > ray_tmax ) { return false; }
    }

    // update hit record
    rec.hit_point = r.At(t);
    rec.normal = ( r.At(t) - center ) / radius;
    rec.t = t;
    rec.mat = mat;
    return true;
}