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

TVector SnellAngleAdjust::ComputeRefractedVelocity(TVector velocity_cell1,
                                                   TVector norm_plane_vector,
                                                   double  speed_in,
                                                   double  speed_out)
{
    // Initialization
    velocity_in = velocity_cell1.Unit();
    norm_plane = norm_plane_vector;
    speed_cell1 = speed_in;
    speed_cell2 = speed_out;
    
    // Check if normal vector of plane is correct
    double cross = norm_plane.Dot(velocity_in);
    double product_magnitude = norm_plane.Abs() * velocity_in.Abs();
    if (abs(abs(cross) - product_magnitude) < 0.0000001)
        return velocity_cell1;
    else if (cross > 0)
        norm_plane = -norm_plane;

    
    // Determine if Refraction or Total Reflection
    double r = speed_cell2 / speed_cell1;
    double c = -norm_plane.Dot(velocity_in);
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
