//
//  snell_angle_adjust.hpp
//
//
//  Created by 施俊宇 on 2016/10/19.
//
//

#ifndef snell_adjust_hpp
#define snell_adjust_hpp

#include "coordinate.hpp"

class SnellAngleAdjust
{
private:
    TVector vector_in, vector_out;
    TVector plane_normal;
    double speed_in, speed_out;

public:
    SnellAngleAdjust() : speed_in(0), speed_out(0) {};

public:
    TVector ComputeRefractedVelocity(const TVector &vector_in,
                                     const TVector &plane_normal,
                                     double         speed_in,
                                     double         speed_out);
};


#endif /* snell_adjust_hpp */
