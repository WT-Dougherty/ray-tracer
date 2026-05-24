#include <boost/test/unit_test.hpp>
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

BOOST_AUTO_TEST_CASE(SphereHitTest)
{
    BOOST_CHECK_EQUAL(true, true);
}

BOOST_AUTO_TEST_SUITE_END()