//
//  snell_angle_adjust.cpp
//  
//
//  Created by 施俊宇 on 2016/10/19.
//
//

#include "snell_angle_adjust.hpp"

TVector ComputeRefractedVelocity(){
    double r, c, coeff;
    
    //Initialization
    r = speed_cell2/speed_cell1;
    c = -norm_plane.Dot(velocity_in);
    //Determine if Refraction or Total Reflection
    if (1 - pow(r, 2) * (1 - pow(c, 2)) >= 0){//Refraction
        coeff = r * c - sqrt(1 - pow(r, 2) * (1 - pow(c, 2)));
        velocity_out = (velocity_in * r + norm_plane * coeff) * speed_cell2;
    }
    else{//Total Reflection
        velocity_out = velocity_in;
        if (norm_plane.x ~= 0)
            velocity_out.x = -velocity_out.x;
        else if(norm_plane.y ~= 0)
            velocity_out.y = -velocity_out.y;
        else
            velocity_out.z = -velocity_out.z;
    }
    
    
    return velocity_out
}