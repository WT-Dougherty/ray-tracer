#include "primaryheader.h"

#include "Environment.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

int main()
{
    // parameters for viewport
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 4000;

    // generate spheres
    auto materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto materialShinyMetal = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));  // shiny metal
    auto materialBlue = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));   // blue
    auto materialYellow = std::make_shared<Lambertian>(Color(0.8, 0.6, 0.2)); // yellow
    auto materialGreen = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));  // green
    auto materialWhite = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.8));  // white
    auto materialPurple = std::make_shared<Lambertian>(Color(1.0, 0.0, 0.0)); // red

    // Sphere* s1 = new Sphere(Point3(0,    -100.5, -1.0), 100.0, materialGround);
    // Sphere* s2 = new Sphere(Point3(0,    0.0,    -1.7), 0.5,   materialShinyMetal);
    // Sphere* s3 = new Sphere(Point3(-1.2, -0.3,   -1.0), 0.2,   materialBlue);
    // Sphere* s4 = new Sphere(Point3(1.1,  0.0,    -1.0), 0.5,   materialYellow);
    // Sphere* s5 = new Sphere(Point3(0,  -0.4,    -1.0), 0.1,   materialShinyMetal);
    // Sphere* s6 = new Sphere(Point3(-0.7,  -0.3,    -1.0), 0.2,   materialShinyMetal);

    Sphere *s1 = new Sphere(Point3(0, -100.5, -1.0), 100.0, materialGround);
    Sphere *s2 = new Sphere(Point3(0, 0.8, -1.7), 1.3, materialShinyMetal);
    Sphere *s3 = new Sphere(Point3(-1.2, -0.3, -1.0), 0.2, materialBlue);
    Sphere *s4 = new Sphere(Point3(-0.2, -0.25, -0.5), 0.25, materialShinyMetal);

    // the environment
    Environment envmt;
    envmt.add(s1);
    envmt.add(s2);
    envmt.add(s3);
    envmt.add(s4);
    // envmt.add( s5 );
    // envmt.add( s6 );

    Camera cam = Camera();
    cam.render(aspectRatio, imageWidth, envmt);

    // memory cleanup
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    // delete s5;
    // delete s6;
}
