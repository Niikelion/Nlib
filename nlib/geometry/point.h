#ifndef POINT_H
#define POINT_H

#include <nlib/geometry/vec.h>

namespace Nlib
{
    class Point2D
    {
    public:
        double  x,y;

        /**
        * \brief Returns linear distance between 2 points.
        */
        double dist(const Point2D&) const noexcept;

        /**
        * \brief Rounds values to given decimal places
        */
        void round(const unsigned int& =0) noexcept;

        bool operator == (const Point2D&) const noexcept;
        bool operator != (const Point2D&) const noexcept;

        Point2D & operator = (const std::initializer_list<double>&) noexcept;
        Point2D& operator = (const Point2D& target) noexcept = default;
        Point2D & operator = (const std::vector<double>&) noexcept;
        Point2D & operator = (Point2D && target) noexcept = default;


        /**
        * \brief Translates point by vector.
        */
        Point2D & operator += (const Vec2& target) noexcept;
        /**
        * \brief Returns point translated by vector.
        */
        Point2D operator + (const Vec2& target) const noexcept;

        /**
        * \brief Translates point by vector.
        */
        Point2D & operator -= (const Vec2& target) noexcept;
        /**
        * \brief Returns point translated by vector.
        */
        Point2D operator - (const Vec2& target) const noexcept;

        /**
        * \brief Returns difference vector.
        */
        Vec2 operator - (const Point2D& target) const noexcept;

        /**
        * \brief Returns point flipped by (0,0) point.
        */
        Point2D operator - () const noexcept;

        /**
        * \brief Scales point.
        */
        Point2D & operator *= (const double& a) noexcept;
        /**
        * \brief Returns scaled point.
        */
        Point2D operator * (const double& a) const noexcept;

        /**
        * \brief Scales point.
        */
        Point2D & operator /= (const double& a) noexcept;
        /**
        * \brief Returns scaled point.
        */
        Point2D operator / (const double& a) const noexcept;

        /**
        * \brief Converts point to vector.
        */
        operator Vec2() const noexcept;
        /**
        * \brief Converts point to vector.
        */
        Vec2 v2() const noexcept;

        Point2D() noexcept;
        Point2D(const Point2D&) noexcept = default;
        Point2D(Point2D&&) noexcept = default;

        Point2D(const double& _x,const double& _y) noexcept;
        Point2D(const Vec2&) noexcept;

        Point2D(const std::initializer_list<double>&) noexcept;
        Point2D(const std::vector<double>&) noexcept;

        virtual ~Point2D() noexcept = default;
    };

    class Point3D:public Point2D
    {
    public:
        double z;

        /**
        * \brief Returns linear distance between 2 points.
        */
        double dist(const Point3D&) const noexcept;

        /**
        * \brief Rounds values to given decimal places
        */
        void round(const unsigned int& =0) noexcept;

        bool operator == (const Point3D&) const noexcept;
        bool operator != (const Point3D&) const noexcept;

        Point3D & operator = (const std::initializer_list<double>&) noexcept;
        Point3D& operator = (const Point3D& target) noexcept = default;
        Point3D & operator = (const std::vector<double>&) noexcept;
        Point3D & operator = (Point3D && target) noexcept = default;


        /**
        * \brief Translates point by vector.
        */
        Point3D & operator += (const Vec3& target) noexcept;
        /**
        * \brief Returns point translated by vector.
        */
        Point3D   operator +  (const Vec3& target) const noexcept;

        /**
        * \brief Translates point by vector.
        */
        Point3D & operator -= (const Vec3& target) noexcept;
        /**
        * \brief Returns point translated by vector.
        */
        Point3D   operator -  (const Vec3& target) const noexcept;

        /**
        * \brief Returns difference vector.
        */
        Vec3      operator -  (const Point3D& target) const noexcept;

        /**
        * \brief Returns point flipped by (0,0) point.
        */
        Point3D   operator -  () const noexcept;

        /**
        * \brief Scales point.
        */
        Point3D & operator *= (const double& a) noexcept;
        /**
        * \brief Returns scaled point.
        */
        Point3D   operator *  (const double& a) const noexcept;

        /**
        * \brief Scales point.
        */
        Point3D & operator /= (const double& a) noexcept;
        /**
        * \brief Returns scaled point.
        */
        Point3D   operator /  (const double& a) const noexcept;

        /**
        * \brief Converts point to vector.
        */
        operator Vec3() const noexcept;
        /**
        * \brief Converts point to vector.
        */
        Vec3 v3() const noexcept;

        Point3D() noexcept;
        Point3D(const Point3D&) noexcept = default;
        Point3D(Point3D&&) noexcept = default;

        Point3D(const double& _x,const double& _y,const double& _z) noexcept;
        Point3D(const Vec3&) noexcept;

        Point3D(const std::initializer_list<double>&) noexcept;
        Point3D(const std::vector<double>&) noexcept;

        virtual ~Point3D() noexcept = default;
    };

    std::ostream& operator << (std::ostream&,const Point2D&);
    std::ostream& operator << (std::ostream&,const Point3D&);
}

#endif // POINT_H
