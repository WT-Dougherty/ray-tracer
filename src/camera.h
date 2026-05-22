#ifndef CAMERA_H
#define CAMERA_H

#include "primaryheader.h"
#include "environment.h"
#include "matter.h"

class Camera
{
private:
    // variables set by user
    double aspectRatio;
    double imageWidth;
    int samplesPerPixel = 100;

    // set variables
    double imageHeight;
    double brightness = 0.5;
    Point3 cameraCenter;
    Vec3 pixelWidth;
    Vec3 pixelHeight;
    Point3 pixelI;

    // functions used during rendering
    void initialize(double ar, double iw);
    Color rayColor(const Ray &r, const Environment &envmt, int depth);
    Vec3 offsetVec();
    Ray getRay(int x, int y);

public:
    Camera() {}
    // camera handles rendering
    void render(double aspectRatio, double imageWidth, const Environment &envmt);
};

#endif /* camera.h */
