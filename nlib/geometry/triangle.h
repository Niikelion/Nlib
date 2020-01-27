#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <nlib/geometry/vec.h>
#include <nlib/geometry/point.h>

namespace Nlib
{
    class Triangle
    {
    public:
        Point3D points[3];

        Triangle() noexcept = default;
        Triangle(const Point3D& a,const Point3D& b ,const Point3D& c) noexcept;
        Triangle(const Triangle&) noexcept = default;
        Triangle(Triangle&&) noexcept = default;
        ~Triangle() = default;
    };

    std::ostream& operator << (std::ostream&,const Triangle&);
}

#endif // TRIANGLE_H
