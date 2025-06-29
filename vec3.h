#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

// utility function
// returns random double in range [0,1)
inline double random_double(double min=0, double max=1) {
    return min + (max-min) * std::rand() / ( RAND_MAX + 1.0 );
}

// consider that some functions may need to be changed to
// references/ values depending on use cases

struct vec3 {

    // vector value
    double val[3];

    // vector initialization & change
    vec3() : val{0, 0, 0} {}
    vec3(double x, double y, double z) : val{x, y, z} {}

    // obtain vector properties
    double X() const { return val[0]; }
    double Y() const { return val[1]; }
    double Z() const { return val[2]; }
    double len_squared() const {
        return val[0]*val[0] + val[1]*val[1] + val[2]*val[2];
    }
    double len() const {
        return std::sqrt( len_squared() );
    }
    bool Zero() const {
        double small = 1e-8;
        if (std::fabs(val[0]) < small && std::fabs(val[1]) < small && std::fabs(val[2]) < small) {
            return true;
        }
        return false;
    }
    vec3 Scale(vec3& v) const {
        return vec3(val[0] * v.X(), val[1] * v.Y(), val[2] * v.Z());
    }
    
    // operations between vectors
    vec3 operator+(vec3 const& vec) const {
        return vec3(val[0] + vec.val[0],
                    val[1] + vec.val[1],
                    val[2] + vec.val[2] );
    }
    vec3 operator-(vec3 const& vec) const {
        return vec3(val[0] - vec.val[0],
                    val[1] - vec.val[1],
                    val[2] - vec.val[2] );
    }
    // dot product
    double operator*(vec3 const& vec) const {
        return (val[0] * vec.val[0] +
                val[1] * vec.val[1] +
                val[2] * vec.val[2] );
    }

    // non-mutating operations on vector
    // ( return new vector )
    vec3 operator*(double t) const {
        return vec3 ( val[0] * t,
                      val[1] * t,
                      val[2] * t );
    }
    vec3 operator/(double t) const {
        return vec3 ( val[0] / t,
                      val[1] / t,
                      val[2] / t );
    }

    // mutating operations on vector
    // ( return mutated vector )
    vec3& operator+=(const vec3& v) {
        val[0] += v.val[0];
        val[1] += v.val[1];
        val[2] += v.val[2];
        return *this;
    }
    vec3& operator*=(double t) {
        val[0] *= t;
        val[1] *= t;
        val[2] *= t;
        return *this;
    }
    vec3& operator/=(double t) { return this->operator*=(1/t); }
    vec3& operator-() { return this->operator*=(-1); }

    static vec3 random(double min, double max) {
        return vec3( random_double(min, max), random_double(min, max), random_double(min, max) );
    }
};

// non-mutating non-member functions
inline vec3 UnitVector(const vec3& v) {
    return v / v.len();
}
inline vec3 operator*(double t, const vec3 v) {
    return v * t;
}
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.val[1] * v.val[2] - u.val[2] * v.val[1],
                u.val[2] * v.val[0] - u.val[0] * v.val[2],
                u.val[0] * v.val[1] - u.val[1] * v.val[0]);
}
inline vec3 random_unit_vector() {
    while (true) {
        vec3 p = vec3::random(-1,1);
        double lensq = p.len_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}
inline bool SameDir(vec3 vector1, vec3 vector2) {
    if ( vector1 * vector2 > 0 ) { return true; }
    return false;
}
inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - ( 2 * (v * n) * n );
}

using point3 = vec3;

#endif /* vec3.h */