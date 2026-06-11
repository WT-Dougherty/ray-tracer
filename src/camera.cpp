#include "camera.h"
#include "material.h"

#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
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

Color Camera ::rayColor(const Ray &r, const Environment &envmt)
{
    Color throughput(1.0, 1.0, 1.0);
    Ray current = r;

    for (int depth = 0; depth < Constants::MAX_RECURSION_DEPTH; depth++)
    {
        HitRecord rec;
        if (!envmt.hit(current, 0.001, infinity, rec))
        {
            Vec3 unitDir = unitVector(current.getDirection());
            auto a = 0.5 * (unitDir.y() + 1.0);
            Color sky = (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
            return throughput.scale(sky);
        }

        Ray scattered;
        Color attenuation;
        if (!rec.mat->scatter(current, rec, attenuation, scattered))
            return Color(0, 0, 0);

        throughput = throughput.scale(attenuation);
        current = scattered;
    }

    return Color(0, 0, 0);
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

    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);

    auto startTime = std::chrono::high_resolution_clock::now();

    std::cout << "P3\n"
              << Constants::IMAGE_WIDTH << ' ' << imageHeight << "\n255\n";

    int height = int(imageHeight);
    int width = Constants::IMAGE_WIDTH;
    unsigned int totalCores = std::thread::hardware_concurrency();
    unsigned int workerCount = (totalCores > 1) ? (totalCores - 1) : 1;

    std::clog << "Rendering with " << workerCount << " thread" << (workerCount == 1 ? "" : "s") << "...\n";

    std::vector<Color> image(height * width);
    std::atomic<int> nextRow{0};

    auto worker = [&](int)
    {
        while (true)
        {
            int rowStart = nextRow.fetch_add(Constants::THREAD_BATCH_SIZE, std::memory_order_relaxed);
            if (rowStart >= height)
                break;

            int rowEnd = std::min(height, rowStart + Constants::THREAD_BATCH_SIZE);
            for (int j = rowStart; j < rowEnd; j++)
            {
                for (int i = 0; i < width; i++)
                {
                    Color pixelColor(0, 0, 0);
                    for (int s = 0; s < Constants::SAMPLES_PER_PIXEL; s++)
                    {
                        Ray r = getRay(i, j);
                        pixelColor += rayColor(r, envmt);
                    }
                    image[j * width + i] = pixelColor / Constants::SAMPLES_PER_PIXEL;
                }
            }
        }
    };

    std::vector<std::thread> workers;
    workers.reserve(workerCount);
    for (unsigned int t = 0; t < workerCount; t++)
        workers.emplace_back(worker, t);

    for (auto &thread : workers)
        thread.join();

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            writeColor(std::cout, image[j * width + i]);
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto renderDuration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);

    std::clog << "\rDone.                 \n";
    std::clog << "Render time: " << renderDuration.count() << " seconds\n";
}
