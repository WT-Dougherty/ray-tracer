#include <boost/test/unit_test.hpp>
#include "sphere.h"
#include "material.h"

// ---------------------------------------------- mocks ----------------------------------------------
class MockLambertian : public Material
{
public:
    bool scatter(const Ray &rIn, const HitRecord &rec, Color &attenuation, Ray &rOut) const override
    {
        return true;
    }
};

class MockMetal : public Material
{
public:
    bool scatter(const Ray &rIn, const HitRecord &rec, Color &attenuation, Ray &rOut) const override
    {
        return true;
    }
};

// ---------------------------------------------- tests ----------------------------------------------
BOOST_AUTO_TEST_SUITE(SphereUnitTests)

BOOST_AUTO_TEST_CASE(SphereDirectHitTest)
{
    auto mat = std::make_shared<MockLambertian>();
    Sphere sphere(Point3(0, 0, -5), 1.0, mat);
    Ray ray(Point3(0, 0, 0), Vec3(0, 0, -1));
    HitRecord rec;

    bool result = sphere.hit(ray, 0.0, 100.0, rec);

    BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE(SphereMissTest)
{
    auto mat = std::make_shared<MockLambertian>();
    Sphere sphere(Point3(0, 0, -5), 1.0, mat);
    Ray ray(Point3(0, 0, 0), Vec3(1, 0, 0));
    HitRecord rec;

    bool result = sphere.hit(ray, 0.0, 100.0, rec);

    BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE(SphereHitRecordTest)
{
    // sphere at (0,0,-5) r=1 — ray hits front face at t=4, point (0,0,-4), normal (0,0,1)
    auto mat = std::make_shared<MockLambertian>();
    Sphere sphere(Point3(0, 0, -5), 1.0, mat);
    Ray ray(Point3(0, 0, 0), Vec3(0, 0, -1));
    HitRecord rec;

    sphere.hit(ray, 0.0, 100.0, rec);

    BOOST_CHECK_CLOSE(rec.t, 4.0, 0.001);
    BOOST_CHECK_CLOSE(rec.hitPoint.z(), -4.0, 0.001);
    BOOST_CHECK_CLOSE(rec.normal.z(), 1.0, 0.001);
    BOOST_CHECK_EQUAL(rec.mat, mat);
}

BOOST_AUTO_TEST_CASE(SphereHitRangeRejectTest)
{
    // sphere at t=4 but tmax=3 — should not register as a hit
    auto mat = std::make_shared<MockMetal>();
    Sphere sphere(Point3(0, 0, -5), 1.0, mat);
    Ray ray(Point3(0, 0, 0), Vec3(0, 0, -1));
    HitRecord rec;

    bool result = sphere.hit(ray, 0.0, 3.0, rec);

    BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE(SphereInsideHitTest)
{
    // ray origin inside sphere — first root is negative, second root at t=5 should be used
    auto mat = std::make_shared<MockLambertian>();
    Sphere sphere(Point3(0, 0, 0), 5.0, mat);
    Ray ray(Point3(0, 0, 0), Vec3(0, 0, -1));
    HitRecord rec;

    bool result = sphere.hit(ray, 0.0, 100.0, rec);

    BOOST_CHECK_EQUAL(result, true);
    BOOST_CHECK_CLOSE(rec.t, 5.0, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()