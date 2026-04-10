#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

// utility function
// returns random double in range [0,1)
inline double randomDouble(double min = 0, double max = 1)
{
    return min + (max - min) * std::rand() / (RAND_MAX + 1.0);
}

// consider that some functions may need to be changed to
// references/ values depending on use cases

struct Vec3
{

    // vector value
    double val[3];

    // vector initialization & change
    Vec3() : val{0, 0, 0} {}
    Vec3(double x, double y, double z) : val{x, y, z} {}

    // obtain vector properties
    double x() const { return val[0]; }
    double y() const { return val[1]; }
    double z() const { return val[2]; }
    double lenSquared() const
    {
        return val[0] * val[0] + val[1] * val[1] + val[2] * val[2];
    }
    double len() const
    {
        return std::sqrt(lenSquared());
    }
    bool zero() const
    {
        double small = 1e-8;
        if (std::fabs(val[0]) < small && std::fabs(val[1]) < small && std::fabs(val[2]) < small)
        {
            return true;
        }
        return false;
    }
    Vec3 scale(Vec3 &v) const
    {
        return Vec3(val[0] * v.x(), val[1] * v.y(), val[2] * v.z());
    }

    // operations between vectors
    Vec3 operator+(Vec3 const &vec) const
    {
        return Vec3(val[0] + vec.val[0],
                    val[1] + vec.val[1],
                    val[2] + vec.val[2]);
    }
    Vec3 operator-(Vec3 const &vec) const
    {
        return Vec3(val[0] - vec.val[0],
                    val[1] - vec.val[1],
                    val[2] - vec.val[2]);
    }
    // dot product
    double operator*(Vec3 const &vec) const
    {
        return (val[0] * vec.val[0] +
                val[1] * vec.val[1] +
                val[2] * vec.val[2]);
    }

    // non-mutating operations on vector
    // ( return new vector )
    Vec3 operator*(double t) const
    {
        return Vec3(val[0] * t,
                    val[1] * t,
                    val[2] * t);
    }
    Vec3 operator/(double t) const
    {
        return Vec3(val[0] / t,
                    val[1] / t,
                    val[2] / t);
    }

    // mutating operations on vector
    // ( return mutated vector )
    Vec3 &operator+=(const Vec3 &v)
    {
        val[0] += v.val[0];
        val[1] += v.val[1];
        val[2] += v.val[2];
        return *this;
    }
    Vec3 &operator*=(double t)
    {
        val[0] *= t;
        val[1] *= t;
        val[2] *= t;
        return *this;
    }
    Vec3 &operator/=(double t) { return this->operator*=(1 / t); }
    Vec3 &operator-() { return this->operator*=(-1); }

    static Vec3 random(double min, double max)
    {
        return Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }
};

// non-mutating non-member functions
inline Vec3 unitVector(const Vec3 &v)
{
    return v / v.len();
}
inline Vec3 operator*(double t, const Vec3 v)
{
    return v * t;
}
inline Vec3 cross(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.val[1] * v.val[2] - u.val[2] * v.val[1],
                u.val[2] * v.val[0] - u.val[0] * v.val[2],
                u.val[0] * v.val[1] - u.val[1] * v.val[0]);
}
inline Vec3 randomUnitVector()
{
    while (true)
    {
        Vec3 p = Vec3::random(-1, 1);
        double lensq = p.lenSquared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}
inline bool sameDir(Vec3 vector1, Vec3 vector2)
{
    if (vector1 * vector2 > 0)
    {
        return true;
    }
    return false;
}
inline Vec3 reflect(const Vec3 &v, const Vec3 &n)
{
    return v - (2 * (v * n) * n);
}

using Point3 = Vec3;

#endif /* vec3.h */
