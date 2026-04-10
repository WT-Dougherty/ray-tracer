#ifndef MATERIAL_H
#define MATERIAL_H

#include "Matter.h"
#include "primaryheader.h"

class Material
{
public:
  virtual ~Material() = default;

  virtual bool scatter(
      const Ray &rIn, const HitRecord &rec, Color &attenuation, Ray &rOut) const
  {
    return false;
  }
};

class Lambertian : public Material
{
private:
  Color albedo;

public:
  Lambertian(const Color &a) : albedo(a) {}
  bool scatter(const Ray &rIn, const HitRecord &rec, Color &attenuation, Ray &rOut) const override
  {
    auto scatterDirection = rec.normal + randomUnitVector();

    if (scatterDirection.zero())
    {
      scatterDirection = rec.normal;
    }

    rOut = Ray(rec.hitPoint, scatterDirection);
    attenuation = albedo;
    return true;
  }
};

class Metal : public Material
{
private:
  Color albedo;

public:
  Metal(const Color &a) : albedo(a) {}
  bool scatter(const Ray &rIn, const HitRecord &rec, Color &attenuation, Ray &rOut) const override
  {
    Vec3 reflected = reflect(rIn.getDirection(), rec.normal);
    rOut = Ray(rec.hitPoint, reflected);
    attenuation = albedo;
    return true;
  }
};

// skeleton code
// TODO: calculate refracted ray direction
//  - origin = rec.hitPoint

class Glass : public Material
{
private:
  Color albedo;

public:
  Glass() {}
  bool scatter(const Ray &rIn, const HitRecord &rec, Color &attenuation, Ray &rOut) const override
  {
    Vec3 refracted = rIn.getDirection();
    rOut = Ray(rec.hitPoint, refracted);
    attenuation = albedo;
    return true;
  }
};

#endif
