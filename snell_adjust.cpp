//
//  snell_angle_adjust.cpp
//
//
//  Created by 施俊宇 on 2016/10/19.
//
//

#include "snell_adjust.hpp"

TVector SnellAngleAdjust::ComputeRefractedVelocity(TVector velocity_cell1,
                                                   TVector norm_plane_vector,
                                                   double  speed_in,
                                                   double  speed_out)
{
    // Initialization
    velocity_in = velocity_cell1 / velocity_cell1.Abs();
    norm_plane = norm_plane_vector;
    speed_cell1 = speed_in;
    speed_cell2 = speed_out;
    double r = speed_cell2/speed_cell1;
    double c = -norm_plane.Dot(velocity_in);

    // Determine if Refraction or Total Reflection
    if (1 - pow(r, 2) * (1 - pow(c, 2)) >= 0)
    {
        // Refraction
        double coeff = r * c - sqrt(1 - pow(r, 2) * (1 - pow(c, 2)));
        velocity_out = (velocity_in * r + norm_plane * coeff) * speed_cell2;
    }
    else
    {
        // Total Reflection
        velocity_out = velocity_in;
        if (norm_plane.x != 0)
            velocity_out.x = -velocity_out.x;
        else if(norm_plane.y != 0)
            velocity_out.y = -velocity_out.y;
        else
            velocity_out.z = -velocity_out.z;
    }

    return velocity_out;
}
