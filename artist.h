#ifndef _HEAD_H
#define _HEAD_H

#include <math.h>

#define PI 3.1415926535897

class P2d{
friend P2d operator+(const P2d& p1, const P2d& p2);
public:
    P2d():x(0.0), y(0.0){}

    P2d(double the_x, double the_y):
        x(the_x), y(the_y){}

    double x;
    double y;
};

class Head
{
public:
    Head(double the_half_angle, double the_radius, int the_half_width):
        half_angle(the_half_angle), radius(the_radius)
    {
        center = P2d(0, 0);
        omega = 5;
        speed = 1;
        half_width = the_half_width;
    }

    enum class PointName
    {
        CENTER, LEFT, RIGHT
    };

    enum  class RotationDirection
    {
        CLOCKWISE, ANTICLOCKWISE
    };

    P2d get_pos(PointName pn)
    {
        if (pn == PointName::CENTER)
            return center;
        P2d pos;
        double ori = orientation;
        if (pn == PointName::LEFT)
            ori += half_angle;
        if (pn == PointName::RIGHT)
            ori -= half_angle;
        pos = center + P2d(radius * cos(ori * PI / 180), radius * sin(ori * PI / 180));
        //std::cout << ori <<" " << pos.x << " " << pos.y << std::endl;
        return pos;
    };

    double get_ori()
    {
        return orientation;
    }

    int Go_ahead()
    {
        P2d new_pos = center + P2d(speed * cos(orientation * PI / 180), speed * sin(orientation * PI / 180));
        if (in_area(new_pos))
            center = new_pos;
        return 0;
    }

    int Turn(RotationDirection rd)
    {
        if (rd == RotationDirection::CLOCKWISE){
            orientation += omega;
            if (orientation > 180)
                orientation -= 360;
        }
        if (rd == RotationDirection::ANTICLOCKWISE){
            orientation -= omega;
            if (orientation < -180)
                orientation += 360;
        }
        return 0;
    }

private:

    int in_area(P2d pos)
    {
        if (fabs(pos.x) < half_width - radius && fabs(pos.y) < half_width - radius)
            return 1;
        return 0;
    }

    P2d center;
    const double half_angle;
    const double radius;

    double orientation; // in degree
    double omega;  // in degree pre frame
    double speed;

    int half_width;
};



#endif // _HEAD_H
