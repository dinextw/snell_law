//
//  snell.cpp
//  Snell_TeacherIII
//
//  Created by 施俊宇 on 2016/10/18.
//  Copyright © 2016年 NCU. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>
#include <cmath>
#include "cuboid.hpp"

using namespace std;

static bool IsParallel(const TVector a, const TVector b)
{
    double scalar_x = a.x / b.x;
    double scalar_y = a.y / b.y;
    double scalar_z = a.z / b.z;


    if (abs(scalar_x - scalar_y) >= 0.0000001)
        return false;
    else if (abs(scalar_x - scalar_z) >= 0.0000001)
        return false;
    else if (abs(scalar_y - scalar_z) >= 0.0000001)
        return false;
    else
        return true;
}

static bool IsOnPlane(const TCoordinate intersection,
                      const TCoordinate corner_left_up,
                      const TCoordinate corner_right_up,
                      const TCoordinate corner_left_down,
                      const TCoordinate corner_right_down)
{

    TVector horizontal_high =
    (intersection - corner_left_up).Cross(corner_right_up - corner_left_up);
    TVector horizontal_low =
    (intersection - corner_right_down).Cross(corner_left_down - corner_right_down);
    TVector vertical_high =
    (intersection - corner_right_up).Cross(corner_right_down - corner_right_up);
    TVector vertical_low =
    (intersection - corner_left_down).Cross(corner_left_up - corner_left_down);

    if (!IsParallel(horizontal_high, horizontal_low))
        return false;
    else if (!IsParallel(horizontal_high, vertical_high))
        return false;
    else if (!IsParallel(horizontal_high, vertical_low))
        return false;
    else if (!IsParallel(horizontal_low, vertical_high))
        return false;
    else if (!IsParallel(horizontal_low, vertical_low))
        return false;
    else if (!IsParallel(vertical_high, vertical_low))
        return false;
    else
        return true;
}

double PlaneCuboid::ComputeDistance(TCoordinate position_in,
                                    TVector velocity_in,
                                    TCoordinate &intersection) const
{
    double scalar = 0;
    double distance = -1;

    if (norm.x != 0)
        scalar = abs((corner_left_up.x - position_in.x) / velocity_in.x);
    else if (norm.y != 0)
        scalar = abs((corner_left_up.y - position_in.y) / velocity_in.y);
    else
        scalar = abs((corner_left_up.z - position_in.z) / velocity_in.z);

    intersection = position_in + velocity_in * scalar;

    bool is_on_plane = IsOnPlane(intersection,
                               corner_left_up,
                               corner_right_up,
                               corner_left_down,
                               corner_right_down);
    if (is_on_plane)
        distance = sqrt(  pow(position_in.x - intersection.x, 2)
                              + pow(position_in.y - intersection.y, 2)
                              + pow(position_in.z - intersection.z, 2) );

    return distance;
};

TVector PlaneCuboid::GetNorm() const{
    return norm;
}

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

static TCoordinate FindIntersection(const double *distance_plane,
                                      const TCoordinate *position_intersect,
                                    int &index)
{
    TCoordinate position_out;
    int index_largest = distance(distance_plane,
                                 max_element(distance_plane, distance_plane + 5));

    for (int i=0; i<6; i++) {
        cout<< distance_plane[i] << endl;
    }
    cout<< index_largest <<endl;
    switch (index_largest) {
        case 0:
            position_out = position_intersect[0];
            index = 0;
            break;
        case 1:
            position_out = position_intersect[1];
            index = 1;
            break;
        case 2:
            position_out = position_intersect[2];
            index = 2;
            break;
        case 3:
            position_out = position_intersect[3];
            index = 3;
            break;
        case 4:
            position_out = position_intersect[4];
            index = 4;
            break;
        case 5:
            position_out = position_intersect[5];
            index = 5;
            break;
        default:
            break;
    }

    return position_out;
}

static TVector GetNormPlaneVector(const PlaneCuboid &plane,
                              const TVector velocity_in){
    TVector norm_plane = plane.GetNorm();
    double cross = norm_plane.Dot(velocity_in);
    double angle = acos(cross / (norm_plane.Abs() * velocity_in.Abs()));

    if (angle < M_PI)
        norm_plane = -norm_plane;

    return norm_plane;

}

static TCoordinate ComputeIntersection(const vector<PlaneCuboid> &plane,
                                       const TCoordinate position_in,
                                       const TVector velocity_in,
                                       TVector &norm_plane)
{
    TCoordinate position_intersect[6];
    double distance_plane[6]={-1};
    int index_norm_plane;
    distance_plane[0] = plane[0].ComputeDistance(position_in,
                                                 velocity_in,
                                                 position_intersect[0]);
    distance_plane[1] = plane[1].ComputeDistance(position_in,
                                                 velocity_in,
                                                 position_intersect[1]);
    distance_plane[2] = plane[2].ComputeDistance(position_in,
                                                 velocity_in,
                                                 position_intersect[2]);
    distance_plane[3] = plane[3].ComputeDistance(position_in,
                                                 velocity_in,
                                                 position_intersect[3]);
    distance_plane[4] = plane[4].ComputeDistance(position_in,
                                                 velocity_in,
                                                 position_intersect[4]);
    distance_plane[5] = plane[5].ComputeDistance(position_in,
                                                 velocity_in,
                                                 position_intersect[5]);

    TCoordinate position_out = FindIntersection(distance_plane,
                                                position_intersect,
                                                index_norm_plane);

    norm_plane = GetNormPlaneVector(plane[index_norm_plane], velocity_in);

    return position_out;
}

pair<TCoordinate, TVector> Cuboid::ComputePath(TCoordinate position_in,
                                               TVector velocity_in) const
{


    // Compute intersection position
    TCoordinate x_high_y_high_z_high(x_high, y_high, z_high);
    TCoordinate x_high_y_high_z_low(x_high, y_high, z_low);
    TCoordinate x_high_y_low_z_high(x_high, y_low, z_high);
    TCoordinate x_high_y_low_z_low(x_high, y_low, z_low);
    TCoordinate x_low_y_high_z_high(x_low, y_high, z_high);
    TCoordinate x_low_y_high_z_low(x_low, y_high, z_low);
    TCoordinate x_low_y_low_z_high(x_low, y_low, z_high);
    TCoordinate x_low_y_low_z_low(x_low, y_low, z_low);

    PlaneCuboid x_low(x_low_y_low_z_high,
                      x_low_y_high_z_high,
                      x_low_y_low_z_low,
                      x_low_y_high_z_low);
    PlaneCuboid x_high(x_high_y_low_z_high,
                       x_high_y_high_z_high,
                       x_high_y_low_z_low,
                       x_high_y_high_z_low);
    PlaneCuboid y_low(x_low_y_low_z_high,
                      x_high_y_low_z_high,
                      x_low_y_low_z_low,
                      x_high_y_low_z_low);
    PlaneCuboid y_high(x_low_y_high_z_high,
                       x_high_y_high_z_high,
                       x_low_y_high_z_low,
                       x_high_y_high_z_low);
    PlaneCuboid z_low(x_low_y_high_z_low,
                      x_high_y_high_z_low,
                      x_low_y_low_z_low,
                      x_high_y_low_z_low);
    PlaneCuboid z_high(x_low_y_high_z_high,
                       x_high_y_high_z_high,
                       x_low_y_low_z_high,
                       x_high_y_low_z_high);

    // Compare Distance
    vector<PlaneCuboid> plane_intersect(6);
    plane_intersect[0] = x_low;
    plane_intersect[1] = x_high;
    plane_intersect[2] = y_low;
    plane_intersect[3] = y_high;
    plane_intersect[4] = z_low;
    plane_intersect[5] = z_high;
    TVector norm_plane;
    TCoordinate position_out = ComputeIntersection(plane_intersect,
                                                   position_in,
                                                   velocity_in,
                                                   norm_plane);


    return pair<TCoordinate, TVector>(position_out, norm_plane);
}
