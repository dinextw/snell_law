//
//  snell.hpp
//  Snell_TeacherIII
//
//  Created by 施俊宇 on 2016/10/18.
//  Copyright © 2016年 NCU. All rights reserved.
//

#ifndef snell_hpp
#define snell_hpp

#include "coordinate.hpp"

class PlaneCuboid
{
private:
    TVector norm;

    TCoordinate corner_left_up, corner_right_up;
    TCoordinate corner_left_down, corner_right_down;

public:
    PlaneCuboid(){};
    PlaneCuboid(TCoordinate corner_left_up,
                TCoordinate corner_right_up,
                TCoordinate corner_left_down,
                TCoordinate corner_right_down)
    : corner_left_up(corner_left_up),
      corner_right_up(corner_right_up),
      corner_left_down(corner_left_down),
      corner_right_down(corner_right_down){
          TVector horizontal = corner_right_up - corner_left_up;
          TVector vertical = corner_right_down - corner_right_up;
          norm = horizontal.Cross(vertical);
    }

public:
    double ComputeDistance(TCoordinate position_in,
                           TVector velocity_in,
                           TCoordinate &intersection) const;
    TVector GetNorm() const;
};

class Cuboid
{
private:
    double x_low, y_low, z_low;
    double x_high, y_high, z_high;
    double speed;

public:
    Cuboid()
        : x_low(0),
          y_low(0),
          z_low(0),
          x_high(0),
          y_high(0),
          z_high(0),
          speed(0)
    {
    }

    Cuboid(const TCoordinate &low_bound, const TCoordinate &high_bound, double speed)
        : x_low(low_bound.x),
          y_low(low_bound.y),
          z_low(low_bound.z),
          x_high(high_bound.x),
          y_high(high_bound.y),
          z_high(high_bound.z),
          speed(speed)
    {
    }

public:
    void SetValue(double x_low,
                  double x_high,
                  double y_low,
                  double y_high,
                  double z_low,
                  double z_high,
                  double speed);

    TCoordinate GetLowBound() const { return TCoordinate(x_low, y_low, z_low); }
    TCoordinate GetHighBound() const { return TCoordinate(x_high, y_high, z_high); }
    double      GetSpeed() const { return speed; }

    std::pair<TCoordinate, TVector> ComputePath(TCoordinate position_in,
                                                TVector velocity_in) const;

};

#endif /* snell_hpp */
