#include <nlib/geometry/plane.h>

namespace Nlib
{
    const Vec3& Plane::vn() const noexcept
    {
        return norm;
    }

    const double& Plane::ds() const noexcept
    {
        return d;
    }

    Plane Plane::operator !() const noexcept
    {
        return Plane(-norm,-d);
    }

    bool Plane::operator == (const Plane& target) const noexcept
    {
        return (norm.unit() == target.norm.unit() && d == target.d)||
                ((-norm).unit() == target.norm.unit() && d == -target.d);
    }

    bool Plane::operator != (const Plane& target) const noexcept
    {
        return (norm.unit() != target.norm.unit() || d != target.d) &&
                ((-norm).unit() != target.norm.unit() || d != -target.d);
    }

    double Plane::distance(const Point3D& a) const noexcept
    {
        double v=(norm.dot(static_cast<Vec3>(a)) + d) / (!norm);


        return (v<0)?-v:v;
    }

    double Plane::offset(const Point3D& a) const noexcept
    {
        return (norm.dot(a) + d) / (!norm);
    }

    bool Plane::parallel(const Plane& a) const noexcept
    {
        return a.norm.unit() == norm.unit() || a.norm.unit() == -norm.unit();
    }

    bool Plane::perp(const Plane& a) const noexcept
    {
        return norm.cos(a.norm)==0;
    }

    Plane& Plane::flip() noexcept
    {
        norm *= -1;
        d *= -1;
        return *this;
    }

    Point3D Plane::mirror(const Point3D& a) const noexcept
    {
        return static_cast<const Vec3&>(a) - norm.unit() * offset(a) * 2;
    }

    Point3D Plane::scale(const Point3D& a,const double& k) const noexcept
    {
        Vec3 b = norm.unit() * offset(a);
        return static_cast<const Vec3&>(a) -b + b * k;
    }

    Plane::Plane() noexcept: d(0){/**/};

    Plane::Plane(const Point3D& a,const Vec3& normal) noexcept: d(-norm.dot(a)), norm(normal) {/**/}

    Plane::Plane(const Vec3& normal,const double& dd) noexcept: d(dd), norm(normal) {/**/}

    Plane::Plane(const Point3D& a,const Point3D& b,const Point3D& c) noexcept: d(-norm.dot(a)), norm((b - a).cross(c - a).unit()) {/**/}
}

//
