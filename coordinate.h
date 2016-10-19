/**
 * Cartesian coordinate point.
 */
#ifndef _COORDINATE_H_
#define _COORDINATE_H_

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
    double Abs() const;
    double Abs2() const;
    TVector Unit() const;
    double Dot(const TVector &v) const ;
    TVector Cross(const TVector &v) const ;

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

#endif
