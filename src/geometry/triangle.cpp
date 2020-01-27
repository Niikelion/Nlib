#include "triangle.h"

namespace Nlib
{
    Triangle::Triangle(const Point3D& a,const Point3D& b ,const Point3D& c) noexcept
    {
        points[0] = a;
        points[1] = b;
        points[2] = c;
    }

    std::ostream& operator << (std::ostream& out,const Triangle& target)
    {
        out << "{" << target.points[0] << "," << target.points[1] << "," << target.points[2] << "}";
        return out;
    }
}
