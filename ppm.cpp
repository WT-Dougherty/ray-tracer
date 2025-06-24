#include "primaryheader.h"

#include "environment.h"
#include "sphere.h"
#include "camera.h"

int main()
{
    // parameters for viewport
    auto aspect_ratio = 16.0/9.0;
    int image_width=400;

    // the environment
    environment envmt;
    sphere* s1 = new sphere(point3(0,-100.5,-1), 100);
    sphere* s2 = new sphere(point3(0,0,-1), 0.5);
    envmt.Add( s1 );
    envmt.Add( s2 );

    Camera cam = Camera();
    cam.Render(aspect_ratio, image_width, envmt);

    // memory cleanup
    delete s1;
    delete s2;

}