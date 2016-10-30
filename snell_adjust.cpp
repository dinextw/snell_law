//
//  snell_angle_adjust.cpp
//
//
//  Created by 施俊宇 on 2016/10/19.
//
//

#include <cmath>
#include "snell_adjust.hpp"

using namespace std;

TVector SnellAngleAdjust::ComputeRefractedVelocity(const TVector &vector_in,
                                                   const TVector &plane_normal,
                                                   double         speed_in,
                                                   double         speed_out)
{
    this->vector_in    = vector_in;
    this->plane_normal = plane_normal;
    this->speed_in     = speed_in;
    this->speed_out    = speed_out;

    TVector normal = plane_normal.Unit();

    // Reverse normal vector if needed.
    double vector_on_normal_size = vector_in.Dot(normal);
    if( vector_on_normal_size < 0 )
    {
        vector_on_normal_size *= -1;
        normal *= -1;
    }

    TVector vector_on_normal  = vector_on_normal_size * normal;
    TVector vector_on_surface = vector_in - vector_on_normal;

    double speed_ratio = speed_in / speed_out;
    double numerator = speed_ratio * speed_ratio * vector_in.Abs2()
                     - vector_on_surface.Abs2();
    double denominator = vector_on_normal.Abs2();

    static const double small_as_zero = 0.000001;
    double factor;
    if( denominator < small_as_zero )
    {
        // Surface parallel.
        factor = 0;
    }
    else if( numerator < 0 )
    {
        // Total refraction.
        factor = -1;
    }
    else
    {
        // Usual refraction.
        factor = sqrt( numerator / denominator );
    }

    return vector_out = ( vector_on_surface + factor * vector_on_normal ).Unit();
}
