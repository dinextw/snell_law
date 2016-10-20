//
//  snell.hpp
//  Snell_TeacherIII
//
//  Created by 施俊宇 on 2016/10/18.
//  Copyright © 2016年 NCU. All rights reserved.
//

#ifndef snell_hpp
#define snell_hpp

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>
#include <cmath>
#include "coordinate.hpp"

using namespace std;

class Cuboid
{
private:
    double x_low, x_high;
    double y_low, y_high;
    double z_low, z_high;

    double speed;

public:
    Cuboid()
    : x_low(0), x_high(0), y_low(0), y_high(0), z_low(0), z_high(0), speed(0) {};
    void SetValue(double x_low_in, double x_high_in, double y_low_in, double y_high_in, double z_low_in, double z_high_in, double speed_in);
    pair <TCoordinate, TVector> ComputePath(TCoordinate position_in, TVector velocity_in);


};

template <typename T>
vector<size_t> SortIndexes(const vector<T> &v)
{

    // initialize original index locations
    vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    sort(idx.begin(), idx.end(),
         [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

    return idx;
}

#endif /* snell_hpp */
