/**
 * Cartesian coordinate point.
 */
#ifndef _COORDINATE_HPP_
#define _COORDINATE_HPP_

#include <math.h>
#include <string>

/**
 * Vector.
 */
class TVector
{
public:
    double x;
    double y;
    double z;

public:
    TVector() : x(0), y(0), z(0) {}
    TVector(double x, double y, double z) : x(x), y(y), z(z) {}
    TVector(const TVector &src) : x(src.x), y(src.y), z(src.z) {}

public:

    inline TVector& operator +=(const TVector &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    inline TVector& operator -=(const TVector &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    inline TVector& operator *=(double s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    inline TVector& operator /=(double s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

public:

    inline double Abs2() const
    {
        // Calculate the absolute value to the power of 2.
        return x*x + y*y + z*z;
    }

    inline double Abs() const
    {
        return sqrt(Abs2());
    }

    inline TVector Unit() const
    {
        double abs_value = Abs();
        return TVector( x / abs_value, y / abs_value, z / abs_value );
    }

    inline double Dot(const TVector &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    inline TVector Cross(const TVector &v) const
    {
        return TVector(y * v.z - z * v.y,
                       z * v.x - x * v.z,
                       x * v.y - y * v.x);
    }

public:
    void FromString(const std::string &str);
    std::string ToString() const;

};

/**
 * Point.
 */
typedef TVector TCoordinate;

/*
 * Global operators.
 */

inline TVector operator +(const TVector &a, const TVector &b)
{
    return TVector( a.x + b.x, a.y + b.y, a.z + b.z );
}

inline TVector operator -(const TVector &a, const TVector &b)
{
    return TVector( a.x - b.x, a.y - b.y, a.z - b.z );
}

inline TVector operator *(const TVector &v, double s)
{
    return TVector( v.x * s, v.y * s, v.z * s );
}

inline TVector operator *(double s, const TVector &v)
{
    return TVector( s * v.x, s * v.y, s * v.z );
}

inline TVector operator /(const TVector &v, double s)
{
    return TVector( v.x / s, v.y / s, v.z / s );
}

inline TVector operator /(double s, const TVector &v)
{
    return TVector( s / v.x, s / v.y, s / v.z );
}

inline TVector operator -(const TVector &v)
{
    return TVector( -v.x, -v.y, -v.z );
}

#endif
