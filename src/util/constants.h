#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants
{
public:
    // ------------------- image parameters ----------------------
    constexpr static const double ASPECT_RATIO = 16.0 / 9.0;
    constexpr static const int IMAGE_WIDTH = 16000;
    constexpr static const int SAMPLES_PER_PIXEL = 100;

    // ------------------- viewport parameters -------------------
    constexpr static const double VIEWPORT_HEIGHT = 2.0;
    constexpr static const double FOCAL_LENGTH = 1.0;

    // ------------------- operational parameters ----------------
    constexpr static const int MAX_RECURSION_DEPTH = 50;
    constexpr static const int THREAD_BATCH_SIZE = 4;
};

#endif /* CONSTANTS_H */