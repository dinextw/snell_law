//
//  snell.hpp
//  Snell_TeacherIII
//
//  Created by 施俊宇 on 2016/10/18.
//  Copyright © 2016年 NCU. All rights reserved.
//

#ifndef snell_hpp
#define snell_hpp

class Cuboid
{
private:
    double x_low, x_up;
    double y_low, y_up;
    double z_low, z_up;
    
    double speed;
    
public:
    Cuboid()
        : x_low(0), x_up(0), y_low(0), y_up(0), z_low(0), z_up(0), speed(0)
    {
    }

};


#endif /* snell_hpp */
