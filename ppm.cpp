#include "primaryheader.h"

#include "environment.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"   

int main()
{
    // parameters for viewport
    auto aspect_ratio = 16.0/9.0;
    int image_width=8000;

    // generate spheres
    auto material_ground      = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_shiny_metal = std::make_shared<metal>(color(0.8, 0.8, 0.8));          // shiny metal
    auto material_blue        = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));     // blue
    auto material_yellow      = std::make_shared<lambertian>(color(0.8, 0.6, 0.2));     // yellow
    auto material_green       = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));     // green
    auto material_white       = std::make_shared<lambertian>(color(0.8, 0.8, 0.8));     // white
    auto material_purple      = std::make_shared<lambertian>(color(1.0, 0.0, 0.0));     // red

    sphere* s1 = new sphere(point3(0,    -100.5, -1.0), 100.0, material_ground);
    sphere* s2 = new sphere(point3(0,    0.0,    -1.7), 0.5,   material_shiny_metal);
    sphere* s3 = new sphere(point3(-1.2, -0.3,   -1.0), 0.2,   material_blue);
    sphere* s4 = new sphere(point3(1.1,  0.0,    -1.0), 0.5,   material_yellow);
    sphere* s5 = new sphere(point3(0,  -0.4,    -1.0), 0.1,   material_shiny_metal);

    // the environment
    environment envmt;
    envmt.Add( s1 );
    envmt.Add( s2 );
    envmt.Add( s3 );
    envmt.Add( s4 );
    envmt.Add( s5 );

    Camera cam = Camera();
    cam.Render(aspect_ratio, image_width, envmt);

    // memory cleanup
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s5;
}