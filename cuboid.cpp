//
//  snell.cpp
//  Snell_TeacherIII
//
//  Created by 施俊宇 on 2016/10/18.
//  Copyright © 2016年 NCU. All rights reserved.
//
#include "cuboid.hpp"

void Cuboid::SetValue(double x_low_in,
                      double x_high_in,
                      double y_low_in,
                      double y_high_in,
                      double z_low_in,
                      double z_high_in,
                      double speed_in)
{
    x_low = x_low_in;
    x_high = x_high_in;

    y_low = y_low_in;
    y_high = y_high_in;

    z_low = z_low_in;
    z_high = z_high_in;

    speed = speed_in;
}

pair<TCoordinate, TVector> Cuboid::ComputePath(TCoordinate position_in, TVector velocity_in)
{
    TCoordinate position_intersect_x_high, position_intersect_x_low;
    TCoordinate position_intersect_y_high, position_intersect_y_low;
    TCoordinate position_intersect_z_high, position_intersect_z_low;

    double factor_multiply_x_high = 0, factor_multiply_x_low = 0;
    double factor_multiply_y_high = 0, factor_multiply_y_low = 0;
    double factor_multiply_z_high = 0, factor_multiply_z_low = 0;

    double distance_x_high = -1, distance_x_low = -1;
    double distance_y_high = -1, distance_y_low = -1;
    double distance_z_high = -1, distance_z_low = -1;

    TCoordinate position_out;
    vector<double> distance(6);
    vector<size_t> index_distance(6);


    //Compute intersection position
    factor_multiply_x_high = abs((x_high - position_in.x) / velocity_in.x);
    factor_multiply_y_high = abs((y_high - position_in.y) / velocity_in.y);
    factor_multiply_z_high = abs((z_high - position_in.z) / velocity_in.z);
    factor_multiply_x_low = abs((x_low - position_in.x) / velocity_in.x);
    factor_multiply_y_low = abs((y_low - position_in.y) / velocity_in.y);
    factor_multiply_z_low = abs((z_low - position_in.z) / velocity_in.z);

    position_intersect_x_high = position_in + velocity_in * factor_multiply_x_high;
    position_intersect_y_high = position_in + velocity_in * factor_multiply_y_high;
    position_intersect_z_high = position_in + velocity_in * factor_multiply_z_high;
    position_intersect_x_low = position_in + velocity_in * factor_multiply_x_low;
    position_intersect_y_low = position_in + velocity_in * factor_multiply_y_low;
    position_intersect_z_low = position_in + velocity_in * factor_multiply_z_low;
    //Compute Distance
    if (position_intersect_x_high.y <= y_high && position_intersect_x_high.y >= y_low && position_intersect_x_high.z <= z_high && position_intersect_x_high.z >= z_low)
        distance_x_high = sqrt(pow(position_in.x - position_intersect_x_high.x, 2) + pow(position_in.y - position_intersect_x_high.y, 2) + pow(position_in.z - position_intersect_x_high.z, 2));
    if (position_intersect_x_low.y <= y_high && position_intersect_x_low.y >= y_low && position_intersect_x_low.z <= z_high && position_intersect_x_low.z >= z_low)
        distance_x_low = sqrt(pow(position_in.x - position_intersect_x_low.x, 2) + pow(position_in.y - position_intersect_x_low.y, 2) + pow(position_in.z - position_intersect_x_low.z, 2));
    if (position_intersect_y_high.x >= x_low && position_intersect_y_high.x <= x_high && position_intersect_y_high.z >= z_low && position_intersect_y_high.z <= z_high)
        distance_y_high = sqrt(pow(position_in.x - position_intersect_y_high.x, 2) + pow(position_in.y - position_intersect_y_high.y, 2) + pow(position_in.z - position_intersect_y_high.z, 2));
    if (position_intersect_y_low.x >= x_low && position_intersect_y_low.x <= x_high && position_intersect_y_low.z >= z_low && position_intersect_y_low.z <= z_high)
        distance_y_low = sqrt(pow(position_in.x - position_intersect_y_low.x, 2) + pow(position_in.y - position_intersect_y_low.y, 2) + pow(position_in.z - position_intersect_y_low.z, 2));
    if (position_intersect_z_high.x >= x_low && position_intersect_z_high.x <= x_high && position_intersect_z_high.y >= y_low && position_intersect_z_high.y <= y_high)
        distance_z_high = sqrt(pow(position_in.x - position_intersect_z_high.x, 2) + pow(position_in.y - position_intersect_z_high.y, 2) + pow(position_in.z - position_intersect_z_high.z, 2));
    if (position_intersect_z_low.x >= x_low && position_intersect_z_low.x <= x_high && position_intersect_z_low.y >= y_low && position_intersect_z_low.y <= y_high)
        distance_z_low = sqrt(pow(position_in.x - position_intersect_z_low.x, 2) + pow(position_in.y - position_intersect_z_low.y, 2) + pow(position_in.z - position_intersect_z_low.z, 2));

    //Compare Distance
    distance[0] = distance_x_high;
    distance[1] = distance_x_low;
    distance[2] = distance_y_high;
    distance[3] = distance_y_low;
    distance[4] = distance_z_high;
    distance[5] = distance_z_low;

    index_distance = SortIndexes(distance);
    //Output Location
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
