#include "camera.h"
#include "material.h"

void Camera ::initialize(double ar, double iw)
{
    aspectRatio = ar;
    imageWidth = iw;

    // calculation of image height
    imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight > 1) ? imageHeight : 1;

    // viewport dimensions
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    auto focalLength = 1.0;
    cameraCenter = Point3(0, 0, 0);

    // calculate vectors across horizontal and down vertical edges
    Vec3 viewportU = Vec3(viewportWidth, 0, 0);
    Vec3 viewportV = Vec3(0, -viewportHeight, 0);

    // pixel dimension (should be ~same)
    pixelWidth = viewportU / double(imageWidth);
    pixelHeight = viewportV / double(imageHeight);

    // calculate initial pixel (upper left)
    Point3 viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    pixelI = viewportUpperLeft + 0.5 * (pixelHeight + pixelWidth);
}

Color Camera ::rayColor(const Ray &r, const Environment &envmt, int depth)
{
    if (depth >= 50)
        return Color(0, 0, 0);
    HitRecord rec;
    if (envmt.hit(r, 0.001, infinity, rec))
    {
        Ray scattered;
        Color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
        {
            return rayColor(scattered, envmt, depth + 1).scale(attenuation);
        }
        return Color(0, 0, 0);
    }

    Vec3 unitDir = unitVector(r.getDirection());
    auto a = 0.5 * (unitDir.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}
Vec3 Camera ::offsetVec()
{
    return Vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
}
Ray Camera ::getRay(int x, int y)
{
    Vec3 ofst = offsetVec();
    auto pixelSample = pixelI + ((x + ofst.x()) * pixelWidth) + ((y + ofst.y()) * pixelHeight);
    Point3 rayOrigin = cameraCenter;
    Vec3 rayDirection = pixelSample - rayOrigin;

    return Ray(rayOrigin, rayDirection);
}

void Camera ::render(double ar, double iw, const Environment &envmt)
{
    initialize(ar, iw);

    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++)
        {
            Color pixelColor = Color(0, 0, 0);
            for (int _ = 0; _ < samplesPerPixel; _++)
            {
                Ray r = getRay(i, j);
                pixelColor += rayColor(r, envmt, 0);
            }
            writeColor(std::cout, pixelColor / samplesPerPixel);
        }
    }
    std::clog << "\rDone.                 \n";
}
