#include "camera.h"

void Camera :: Initialize(double ar, double iw)
{
    aspect_ratio = ar;
    image_width = iw;

    // calculation of image height
    image_height = int ( image_width / aspect_ratio );
    image_height = ( image_height > 1 ) ? image_height : 1;

    // viewport dimensions
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ( double(image_width) / image_height );
    auto focal_length = 1.0;
    camera_center = point3(0, 0, 0);

    // calculate vectors across horizontal and down vertical edges
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // pixel dimension (should be ~same)
    pixel_width = viewport_u / double( image_width );
    pixel_height = viewport_v / double( image_height );

    // calculate initial pixel (upper left)
    point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length)
                                               - viewport_u/2
                                               - viewport_v/2;
    pixel_i = viewport_upper_left + 0.5 * (pixel_height + pixel_width);
}

color Camera :: Ray_Color(const ray& r, const environment& envmt) {
    hit_record rec;
    if ( envmt.hit(r, 0, infinity, rec) )
    {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_dir = UnitVector( r.Direction() );
    auto a = 0.5 * (unit_dir.Y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0)
               + a*color(0.5, 0.7, 1.0);
}

void Camera :: Render(double ar, double iw, const environment& envmt)
{
    Initialize(ar, iw);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            point3 pixel_pos = pixel_i + pixel_width*i + pixel_height*j;
            vec3 dir = pixel_pos - camera_center;
            ray r(camera_center, dir);

            color pixel_color = Ray_Color(r, envmt);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}