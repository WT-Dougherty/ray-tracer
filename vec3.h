#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

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
    vec3 UnitVector() const {
        return *this / len();
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
        return this->operator*(1.0/t);
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
    vec3& operator/=(double t) { return *this *= 1/t; }
    vec3& operator-() { return *this *= -1; }
};

// non-mutating non-member functions
vec3 operator*(double t, const vec3 v) {
    return vec3( t*v.X(), t*v.Y(), t*v.Z() );
}

using point3 = vec3;

#endif /* vec3.h */