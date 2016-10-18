/**
 * Cartesian coordinate point.
 */
#ifndef _COORDINATE_H_
#define _COORDINATE_H_

/**
 * Point.
 */
class TCoordinate
{
public:
    double x;
    double y;
    double z;

public:
    TCoordinate() : x(0), y(0), z(0) {}
    TCoordinate(double x, double y, double z) : x(x), y(y), z(z) {}
    TCoordinate(const TCoordinate &src) : x(src.x), y(src.y), z(src.z) {}

};

/**
 * Vector.
 */
typedef TCoordinate TVector;

#endif
