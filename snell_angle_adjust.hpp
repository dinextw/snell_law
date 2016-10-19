//
//  snell_angle_adjust.hpp
//  
//
//  Created by 施俊宇 on 2016/10/19.
//
//

#ifndef snell_angle_adjust_hpp
#define snell_angle_adjust_hpp

#include "TCoordinate.hpp"

class SnellAngleAdjust
{
private:
    TVector velocity_in, velocity_out;
    TVector norm_plane;
    double speed_cell1, speed_cell2;
    
public:
    SnellAngleAdjust(TVector velocity_cell1, speed_cell1, speed_cell2, norm_plane) : velocity_in(velocity_cell1), speed_cell1(speed_cell1), speed_cell2(speed_cell2), norm_plane(norm_plane){};
    TVector ComputeRefractedVelocity();
}


#endif /* snell_angle_adjust_hpp */
