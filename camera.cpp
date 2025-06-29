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

color Camera :: Ray_Color(const ray& r, const environment& envmt, int depth) {
    if (depth >= 50) return color(0,0,0);
    hit_record rec;
    if ( envmt.hit(r, 0.001, infinity, rec) )
    {
        vec3 dir = random_unit_vector();
        if ( !SameDir(dir, rec.normal) ) { dir *= -1; }
        return 0.5 * Ray_Color( ray(rec.hit_point, dir), envmt, depth+1 );
    }

    vec3 unit_dir = UnitVector( r.Direction() );
    auto a = 0.5 * (unit_dir.Y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0)
               + a*color(0.5, 0.7, 1.0);
}
vec3 Camera :: OffsetVec() {
    return vec3(random_double()-0.5, random_double()-0.5, 0);
}
ray Camera :: GetRay(int x, int y) {
    vec3 os = OffsetVec();
    auto pixel_sample = pixel_i
                        + ((x + os.X()) * pixel_width)
                        + ((y + os.Y()) * pixel_height);
    point3 ray_origin = camera_center;
    vec3 ray_direction = pixel_sample - ray_origin;
    
    return ray(ray_origin, ray_direction);
}

void Camera :: Render(double ar, double iw, const environment& envmt)
{
    Initialize(ar, iw);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            color pixel_color = color(0,0,0);
            for (int _=0; _<samples_per_pixel; _++) {
                ray r = GetRay(i, j);
                pixel_color += Ray_Color(r, envmt, 0);
            }
            write_color(std::cout, pixel_color / samples_per_pixel);
        }
    }
    std::clog << "\rDone.                 \n";
}