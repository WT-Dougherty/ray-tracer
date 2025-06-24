#ifndef CAMERA_H
#define CAMERA_H

#include "primaryheader.h"
#include "environment.h"
#include "matter.h"

class Camera {
private:
    // variables set by user
    double aspect_ratio;
    double image_width;
    
    // set variables
    double image_height;
    point3 camera_center;
    vec3 pixel_width;
    vec3 pixel_height;
    point3 pixel_i;

    // functions used during rendering
    void Initialize(double ar, double iw);
    color Ray_Color(const ray& r, const environment& envmt);
public:
    Camera() {}
    // camera handles rendering
    void Render(double aspect_ratio, double image_width, const environment& envmt);
};

#endif /* camera.h */