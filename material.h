#ifndef MATERIAL_H
#define MATERIAL_H

#include "matter.h"
#include "primaryheader.h"

class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& r_out ) const 
            { return false; }
};

class lambertian : public material {
private:
  color albedo;
public:
  lambertian(const color& a) : albedo(a) {}
  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& r_out ) const override {
    auto scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.Zero()) {
      scatter_direction = rec.normal;
    }

    r_out = ray(rec.hit_point, scatter_direction);
    attenuation = albedo;
    return true;
  }
};

class metal : public material {
private:
  color albedo;
public:
  metal(const color& a) : albedo(a) {}
  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& r_out ) const override {
    vec3 reflected = reflect(r_in.Direction(), rec.normal);
    r_out = ray(rec.hit_point, reflected);
    attenuation = albedo;
    return true;
  }
};
#endif