#ifndef PLANE_H
#define PLANE_H

#include <nlib/geometry/vec.h>
#include <nlib/geometry/point.h>

namespace Nlib
{
    class Plane
    {
        double d;
        Vec3 norm;
    public:
        /**
        * \brief Returns vector normal to plane.
        */
        const Vec3& vn() const noexcept;
        /**
        * \brief Returns d from plane equation.
        */
        const double& ds() const noexcept;
        /**
        * \brief Returns plane with flipped orientation.
        */
        Plane operator !() const noexcept;

        Plane& operator = (const Plane&) noexcept = default;
        Plane& operator = (Plane&&) noexcept = default;

        bool operator == (const Plane&) const noexcept;
        bool operator != (const Plane&) const noexcept;

        /**
        * \brief Returns distance of given point to string.
        */
        double distance(const Point3D&) const noexcept;
        /**
        * \brief Returns offset of given point to string.
        *
        * \note It is similar to distance, but gives negative values for points on the opposite  site of plane.
        */
        double offset  (const Point3D&) const noexcept;

        /**
        * \brief Returns true if planes are parallel.
        */
        bool parallel(const Plane&) const noexcept;
        /**
        * \brief Returns true if planes are perpendicular.
        */
        bool perp(const Plane&) const noexcept;

        /**
        * \brief Flips plane(inverts normal vector).
        *
        * \note It has similar functionality to ! operator but it also modifies itself.
        */
        Plane& flip() noexcept;

        /**
        * \brief Returns point mirrored by plane.
        */
        Point3D mirror(const Point3D&) const noexcept;
        /**
        * \brief Scales point by plane and scale.
        */
        Point3D scale (const Point3D&,const double&) const noexcept;

        Plane() noexcept;
        Plane(const Plane&) noexcept = default;
        Plane(Plane&&) noexcept = default;
        Plane(const Point3D& a,const Vec3& normal) noexcept;
        Plane(const Vec3& normal,const double& dd) noexcept;
        Plane(const Point3D& a,const Point3D& b,const Point3D& c) noexcept;

        virtual ~Plane() noexcept = default;
    };
}

#endif // PLANE_H
