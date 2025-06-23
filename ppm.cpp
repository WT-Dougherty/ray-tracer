#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <iostream>

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 cmo = center - r.Origin();
    auto a = r.Direction() * r.Direction();
    auto h = r.Direction()*cmo;
    auto c = (cmo*cmo) - (radius*radius);
    auto discriminant = h*h - a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        auto t = (h - std::sqrt(discriminant) ) / a;
        return t;
    }
}

color ray_color(const ray& r) {
    double t = hit_sphere( point3(0, 0, -1), 0.5, r );
    if (t > 0) {
        vec3 N = UnitVector( (r.At(t) - vec3(0, 0, -1)) );
        return 0.5*color(N.X()+1, N.Y()+1, N.Z()+1);
    }

    vec3 unit_dir = UnitVector( r.Direction() );
    auto a = 0.5 * (unit_dir.Y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0)
               + a*color(0.5, 0.7, 1.0);
}

int main()
{
    // parameters for viewport
    auto aspect_ratio = 16.0/9.0;
    int image_width=400;

    // calculation of image height
    int image_height = int ( image_width / aspect_ratio );
    image_height = ( image_height > 1 ) ? image_height : 1;

    // viewport dimensions
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * ( double(image_width) / image_height );
    auto focal_length = 1.0;
    point3 camera_center = point3(0, 0, 0);

    // calculate vectors across horizontal and down vertical edges
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // pixel dimension (should be ~same)
    auto pixel_width = viewport_u / double( image_width );
    auto pixel_height = viewport_v / double( image_height );

    // calculate initial pixel (upper left)
    point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length)
                                               - viewport_u/2
                                               - viewport_v/2;
    point3 pixel_i = viewport_upper_left + 0.5 * (pixel_height + pixel_width);

    // render image
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            point3 pixel_pos = pixel_i + pixel_width*i + pixel_height*j;
            vec3 dir = pixel_pos - camera_center;
            ray r(camera_center, dir);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}