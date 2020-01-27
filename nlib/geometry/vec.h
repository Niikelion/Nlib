#ifndef Vec_H
#define Vec_H

#include <initializer_list>
#include <cinttypes>
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

namespace Nlib
{
    /**
    * \class Vec2
    * \brief Basic 2D vector class.
    */
    class Vec2
    {
    public:
        double  x,/**< Vector x member. */
                y;/**< Vector y member. */

        /**
        * \brief Returns unit vector.
        */
        Vec2 unit() const noexcept;
        /**
        * \brief Returns length of vector.
        */
        double length() const noexcept;
        /**
        * \brief Returns dot product of itself and \a target.
        */
        double dot(const Vec2& target) const noexcept;
        /**
        * \brief Returns pseudo cross product of itself and \a target.
        */
        double perpp(const Vec2& target) const noexcept;
        /**
        * \brief Returns length of vector.
        */

        double angle(const Vec2& target) const noexcept;
        double cos(const Vec2& target) const noexcept;
        double sin(const Vec2& target) const noexcept;

        double operator !() const noexcept;

        bool operator == (const Vec2&) const noexcept;
        bool operator != (const Vec2&) const noexcept;

        bool parallel(const Vec2&) const noexcept;
        bool perp(const Vec2&) const noexcept;


        Vec2 & operator = (const std::initializer_list<double>&) noexcept;
        Vec2 & operator = (const Vec2& target) noexcept = default;
        Vec2 & operator = (const std::vector<double>&) noexcept;
        Vec2 & operator = (Vec2 && target) noexcept = default;


        Vec2 & operator += (const Vec2& target) noexcept;
        Vec2 operator + (const Vec2& target) const noexcept;

        Vec2 & operator -= (const Vec2& target) noexcept;
        Vec2 operator - (const Vec2& target) const noexcept;
        Vec2 operator - () const noexcept;

        Vec2 & operator *= (const double& a) noexcept;
        Vec2 operator * (const double& a) const noexcept;

        Vec2 & operator /= (const double& a) noexcept;
        Vec2 operator / (const double& a) const noexcept;

        Vec2() noexcept;
        Vec2(const double& _x,const double& _y) noexcept;
        Vec2(const Vec2& target) noexcept = default;
        Vec2(Vec2&& target) noexcept = default;

        Vec2(const std::initializer_list<double>&) noexcept;
        Vec2(const std::vector<double>&) noexcept;

        virtual ~Vec2() noexcept = default;
    };
    /**
    * \class Vec3
    * \brief Basic 3D vector class.
    */
    class Vec3:public Vec2
    {
    public:
        double z;/**< Vector z member. */

        /**
        * \brief Returns unit vector.
        */
        Vec3 unit() const noexcept;
        /**
        * \brief Returns length of vector.
        */
        double length() const noexcept;
        /**
        * \brief Returns dot product of itself and \a target.
        */
        double dot(const Vec3& target) const noexcept;
        /**
        * \brief Return cross product of itself and \a target.
        */
        Vec3 cross(const Vec3& target) const noexcept;
        /**
        * \brief Returns length of vector.
        */

        double angle(const Vec3& target) const noexcept;
        double sin(const Vec3& target) const noexcept;
        double cos(const Vec3& target) const noexcept;

        double operator !() const noexcept;

        bool operator == (const Vec3&) const noexcept;
        bool operator != (const Vec3&) const noexcept;

        bool parallel(const Vec3&) const noexcept;
        bool perp(const Vec3&) const noexcept;

        Vec3 & operator = (const std::initializer_list<double>&) noexcept;
        Vec3 & operator = (const Vec3& target) noexcept = default;
        Vec3 & operator = (const std::vector<double>&) noexcept;
        Vec3 & operator = (Vec3 && target) noexcept = default;

        Vec3 & operator += (const Vec3& target) noexcept;
        Vec3 operator + (const Vec3& target) const noexcept;

        Vec3 & operator -= (const Vec3& target) noexcept;
        Vec3 operator - (const Vec3& target) const noexcept;
        Vec3 operator - () const noexcept;

        Vec3 & operator *= (const double& a) noexcept;
        Vec3 & operator *= (const Vec3& target) noexcept;

        Vec3 operator * (const double& a) const noexcept;
        Vec3 operator * (const Vec3& target) const noexcept;

        Vec3 & operator /= (const double& a) noexcept;
        Vec3 operator / (const double& a) const noexcept;

        Vec3() noexcept;
        Vec3(const double& _x,const double& _y,const double& _z) noexcept;
        Vec3(const Vec3& target) noexcept = default;
        Vec3(Vec3&& target) noexcept = default;

        Vec3(const std::initializer_list<double>&) noexcept;
        Vec3(const std::vector<double>&) noexcept;

        virtual ~Vec3() noexcept = default;
    };
    std::ostream& operator << (std::ostream&,const Vec2&);
    std::ostream& operator << (std::ostream&,const Vec3&);
}
#endif // Vec_H
