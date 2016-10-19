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
    TVector& operator +=(const TVector &v);
    TVector& operator -=(const TVector &v);
    TVector& operator *=(double s);
    TVector& operator /=(double s);

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
TVector operator +(const TVector &a, const TVector &b);
TVector operator -(const TVector &a, const TVector &b);
TVector operator *(const TVector &v, double s);
TVector operator *(double s, const TVector &v);
TVector operator /(const TVector &v, double s);
TVector operator /(double s, const TVector &v);

#endif
