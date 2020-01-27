#ifndef FRAME_H
#define FRAME_H

#include <nlib/geometry/plane.h>

namespace Nlib
{
    /**
    * \class Frame
    * \brief Frame of reference class.
    */
    class Frame
    {
        Plane x,y,z;

        static double getDet(double [][3]) noexcept;

    public:
        /**
        * \brief Returns center point reference frame.
        */
        Point3D center() const noexcept;

        /**
        * \brief Returns given position relative to frame.
        */
        Point3D relative(const Point3D&) const noexcept;

        /**
        * \brief Returns given position outside of a frame.
        */
        Point3D outside(const Point3D&) const noexcept;

        Frame& operator = (const Frame&) noexcept = default;
        Frame& operator = (Frame&&) noexcept = default;


        Frame() noexcept;
        Frame(const Frame&) noexcept = default;
        Frame(Frame&&) noexcept = default;

        Frame(const Plane&,const Plane&,const Plane&) noexcept;
        Frame(const Vec3&,const Vec3&,const Vec3&,const Point3D& = Point3D(0,0,0)) noexcept;

        virtual ~Frame() noexcept = default;
    };
}

#endif // FRAME_H
