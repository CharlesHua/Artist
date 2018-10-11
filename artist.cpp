
#include "artist.h"


P2d operator+(const P2d& p1, const P2d& p2)
{
    P2d point;
    point.x = p1.x + p2.x;
    point.y = p1.y + p2.y;
    return point;
}
