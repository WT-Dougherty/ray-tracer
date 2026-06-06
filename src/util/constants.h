#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants
{
public:
    // ------------------- image parameters -------------------
    constexpr static const double ASPECT_RATIO = 16.0 / 9.0;
    constexpr static const int IMAGE_WIDTH = 400;

    // ------------------- viewport parameters -------------------
    constexpr static const double VIEWPORT_HEIGHT = 2.0;
    constexpr static const double FOCAL_LENGTH = 1.0;
};

#endif // CONSTANTS_H