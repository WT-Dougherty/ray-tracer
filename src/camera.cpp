#include "camera.h"
#include "material.h"

#include "util/constants.h"

void Camera ::initialize()
{
    // calculation of image height
    imageHeight = int(Constants::IMAGE_WIDTH / Constants::ASPECT_RATIO);
    imageHeight = (imageHeight > 1) ? imageHeight : 1;

    // viewport dimensions
    double viewportWidth = Constants::VIEWPORT_HEIGHT * (double(Constants::IMAGE_WIDTH) / imageHeight);
    cameraCenter = Point3(0, 0, 0);

    // calculate vectors across horizontal and down vertical edges
    Vec3 viewportU = Vec3(viewportWidth, 0, 0);
    Vec3 viewportV = Vec3(0, -Constants::VIEWPORT_HEIGHT, 0);

    // pixel dimension (should be ~same)
    pixelWidth = viewportU / double(Constants::IMAGE_WIDTH);
    pixelHeight = viewportV / double(imageHeight);

    // calculate initial pixel (upper left)
    Point3 viewportUpperLeft = cameraCenter - Vec3(0, 0, Constants::FOCAL_LENGTH) - viewportU / 2 - viewportV / 2;
    pixelI = viewportUpperLeft + 0.5 * (pixelHeight + pixelWidth);
}

Color Camera ::rayColor(const Ray &r, const Environment &envmt, int depth)
{
    if (depth >= Constants::MAX_RECURSION_DEPTH)
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

void Camera ::render(const Environment &envmt)
{
    initialize();

    std::cout << "P3\n"
              << Constants::IMAGE_WIDTH << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < Constants::IMAGE_WIDTH; i++)
        {
            Color pixelColor = Color(0, 0, 0);
            for (int _ = 0; _ < Constants::SAMPLES_PER_PIXEL; _++)
            {
                Ray r = getRay(i, j);
                pixelColor += rayColor(r, envmt, 0);
            }
            writeColor(std::cout, pixelColor / Constants::SAMPLES_PER_PIXEL);
        }
    }
    std::clog << "\rDone.                 \n";
}
