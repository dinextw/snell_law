//
//  snell.cpp
//  Snell_TeacherIII
//
//  Created by 施俊宇 on 2016/10/18.
//  Copyright © 2016年 NCU. All rights reserved.
//
#include "cuboid.hpp"

void Cuboid::SetValue(double x_low,
                      double x_high,
                      double y_low,
                      double y_high,
                      double z_low,
                      double z_high,
                      double speed)
{
    this->x_low = x_low;
    this->x_high = x_high;

    this->y_low = y_low;
    this->y_high = y_high;

    this->z_low = z_low;
    this->z_high = z_high;

    this->speed = speed;
}

pair<TCoordinate, TVector> Cuboid::ComputePath(TCoordinate position_in, TVector velocity_in)
{
    // Compute intersection position

    double factor_multiply_x_high = abs((x_high - position_in.x) / velocity_in.x);
    double factor_multiply_y_high = abs((y_high - position_in.y) / velocity_in.y);
    double factor_multiply_z_high = abs((z_high - position_in.z) / velocity_in.z);
    double factor_multiply_x_low = abs((x_low - position_in.x) / velocity_in.x);
    double factor_multiply_y_low = abs((y_low - position_in.y) / velocity_in.y);
    double factor_multiply_z_low = abs((z_low - position_in.z) / velocity_in.z);

    TCoordinate position_intersect_x_high = position_in + velocity_in * factor_multiply_x_high;
    TCoordinate position_intersect_y_high = position_in + velocity_in * factor_multiply_y_high;
    TCoordinate position_intersect_z_high = position_in + velocity_in * factor_multiply_z_high;
    TCoordinate position_intersect_x_low = position_in + velocity_in * factor_multiply_x_low;
    TCoordinate position_intersect_y_low = position_in + velocity_in * factor_multiply_y_low;
    TCoordinate position_intersect_z_low = position_in + velocity_in * factor_multiply_z_low;

    // Compute Distance

    double distance_x_high = -1;
    if( position_intersect_x_high.y <= y_high &&
        position_intersect_x_high.y >= y_low &&
        position_intersect_x_high.z <= z_high &&
        position_intersect_x_high.z >= z_low )
    {
        distance_x_high = sqrt(  pow(position_in.x - position_intersect_x_high.x, 2)
                               + pow(position_in.y - position_intersect_x_high.y, 2)
                               + pow(position_in.z - position_intersect_x_high.z, 2) );
    }

    double distance_x_low = -1;
    if( position_intersect_x_low.y <= y_high &&
        position_intersect_x_low.y >= y_low &&
        position_intersect_x_low.z <= z_high &&
        position_intersect_x_low.z >= z_low)
    {
        distance_x_low = sqrt(  pow(position_in.x - position_intersect_x_low.x, 2)
                              + pow(position_in.y - position_intersect_x_low.y, 2)
                              + pow(position_in.z - position_intersect_x_low.z, 2) );
    }

    double distance_y_high = -1;
    if( position_intersect_y_high.x >= x_low &&
        position_intersect_y_high.x <= x_high &&
        position_intersect_y_high.z >= z_low &&
        position_intersect_y_high.z <= z_high)
    {
        distance_y_high = sqrt(  pow(position_in.x - position_intersect_y_high.x, 2)
                               + pow(position_in.y - position_intersect_y_high.y, 2)
                               + pow(position_in.z - position_intersect_y_high.z, 2) );
    }

    double distance_y_low = -1;
    if( position_intersect_y_low.x >= x_low &&
        position_intersect_y_low.x <= x_high &&
        position_intersect_y_low.z >= z_low &&
        position_intersect_y_low.z <= z_high)
    {
        distance_y_low = sqrt(  pow(position_in.x - position_intersect_y_low.x, 2)
                              + pow(position_in.y - position_intersect_y_low.y, 2)
                              + pow(position_in.z - position_intersect_y_low.z, 2) );
    }

    double distance_z_high = -1;
    if( position_intersect_z_high.x >= x_low &&
        position_intersect_z_high.x <= x_high &&
        position_intersect_z_high.y >= y_low &&
        position_intersect_z_high.y <= y_high)
    {
        distance_z_high = sqrt(  pow(position_in.x - position_intersect_z_high.x, 2)
                               + pow(position_in.y - position_intersect_z_high.y, 2)
                               + pow(position_in.z - position_intersect_z_high.z, 2) );
    }

    double distance_z_low = -1;
    if( position_intersect_z_low.x >= x_low &&
        position_intersect_z_low.x <= x_high &&
        position_intersect_z_low.y >= y_low &&
        position_intersect_z_low.y <= y_high)
    {
        distance_z_low = sqrt(  pow(position_in.x - position_intersect_z_low.x, 2)
                              + pow(position_in.y - position_intersect_z_low.y, 2)
                              + pow(position_in.z - position_intersect_z_low.z, 2) );
    }

    // Compare Distance

    vector<double> distance(6);
    distance[0] = distance_x_high;
    distance[1] = distance_x_low;
    distance[2] = distance_y_high;
    distance[3] = distance_y_low;
    distance[4] = distance_z_high;
    distance[5] = distance_z_low;

    // Output Location

    vector<size_t> index_distance = SortIndexes(distance);
    TCoordinate position_out;
    switch (index_distance[5]) {
        case 0:
            position_out = position_intersect_x_high;
            break;
        case 1:
            position_out = position_intersect_x_low;
            break;
        case 2:
            position_out = position_intersect_y_high;
            break;
        case 3:
            position_out = position_intersect_y_low;
            break;
        case 4:
            position_out = position_intersect_z_high;
            break;
        case 5:
            position_out = position_intersect_z_low;
            break;
        default:
            break;
    }


    return pair<TCoordinate, TVector>(position_out, velocity_in);
}
