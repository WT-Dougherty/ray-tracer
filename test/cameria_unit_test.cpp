#include <boost/test/unit_test.hpp>
#include <sstream>
#include "camera.h"
#include "environment.h"
#include "util/constants.h"

// ---------------------------------------------- tests ----------------------------------------------
BOOST_AUTO_TEST_SUITE(CameraUnitTests)

BOOST_AUTO_TEST_CASE(CameraConstructTest)
{
    Camera cam;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(CameraRenderPPMHeaderTest)
{
    // redirect stdout so render() output can be inspected
    std::streambuf *oldCout = std::cout.rdbuf();
    std::ostringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());

    Camera cam;
    Environment env;
    cam.render(env);

    std::cout.rdbuf(oldCout);

    std::string output = buffer.str();
    BOOST_CHECK_EQUAL(output.substr(0, 2), "P3");
}

BOOST_AUTO_TEST_CASE(CameraRenderDimensionsTest)
{
    // verify rendered output declares the expected image dimensions
    std::streambuf *oldCout = std::cout.rdbuf();
    std::ostringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());

    Camera cam;
    Environment env;
    cam.render(env);

    std::cout.rdbuf(oldCout);

    std::string output = buffer.str();
    // PPM header line 2: "<width> <height>"
    std::size_t firstNewline = output.find('\n');
    std::string headerLine = output.substr(firstNewline + 1, output.find('\n', firstNewline + 1) - firstNewline - 1);
    std::ostringstream expected;
    expected << Constants::IMAGE_WIDTH << ' ' << int(Constants::IMAGE_WIDTH / Constants::ASPECT_RATIO);
    BOOST_CHECK_EQUAL(headerLine, expected.str());
}

BOOST_AUTO_TEST_SUITE_END()
