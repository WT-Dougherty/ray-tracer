#include <boost/test/unit_test.hpp>
#include "sphere.h"
#include "environment.h"
#include "material.h"

// ---------------------------------------------- tests ----------------------------------------------
BOOST_AUTO_TEST_SUITE(SphereIntegrationTests)

BOOST_AUTO_TEST_CASE(SphereInEnvironmentHitTest)
{
    auto mat = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    Sphere sphere(Point3(0, 0, -5), 1.0, mat);
    Environment env;
    env.add(&sphere);

    Ray ray(Point3(0, 0, 0), Vec3(0, 0, -1));
    HitRecord rec;

    bool result = env.hit(ray, 0.0, 100.0, rec);

    BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE(SphereInEnvironmentMissTest)
{
    auto mat = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    Sphere sphere(Point3(0, 0, -5), 1.0, mat);
    Environment env;
    env.add(&sphere);

    Ray ray(Point3(0, 0, 0), Vec3(1, 0, 0));
    HitRecord rec;

    bool result = env.hit(ray, 0.0, 100.0, rec);

    BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE(EmptyEnvironmentMissTest)
{
    Environment env;
    Ray ray(Point3(0, 0, 0), Vec3(0, 0, -1));
    HitRecord rec;

    bool result = env.hit(ray, 0.0, 100.0, rec);

    BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE(SphereHitRecordPopulatedTest)
{
    auto mat = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
    Sphere sphere(Point3(0, 0, -5), 1.0, mat);
    Environment env;
    env.add(&sphere);

    Ray ray(Point3(0, 0, 0), Vec3(0, 0, -1));
    HitRecord rec;
    env.hit(ray, 0.0, 100.0, rec);

    BOOST_CHECK_CLOSE(rec.t, 4.0, 0.001);
    BOOST_CHECK_CLOSE(rec.hitPoint.z(), -4.0, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()
