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
    TVector velocity_in, velocity_out;
    TVector norm_plane;
    double speed_cell1, speed_cell2;

public:
    SnellAngleAdjust() : speed_cell1(0), speed_cell2(0){};

public:
    TVector ComputeRefractedVelocity(TVector velocity_cell1,
                                     TVector norm_plane_vector,
                                     double  speed_in,
                                     double  speed_out);
};


#endif /* snell_adjust_hpp */
