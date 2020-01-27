#include <nlib/geometry/point.h>

namespace Nlib
{
    double Point2D::dist(const Point2D& target)const noexcept
    {
        return sqrt(pow(x-target.x,2)+pow(y-target.y,2));
    }

    void Point2D::round(const unsigned int& a) noexcept
    {
        const unsigned int p = pow(10,a);
        x = std::round(x*p) / p;
        if (x==-0.0d)
            x=0;
        y = std::round(y*p) / p;
        if (y==-0.0d)
            y=0;
    }

    bool Point2D::operator == (const Point2D& target) const noexcept
    {
        return x == target.x && y==target.y;
    }

    bool Point2D::operator != (const Point2D& target) const noexcept
    {
        return x != target.x || y != target.y;
    }

    Point2D & Point2D::operator = (const std::initializer_list<double>& l) noexcept
    {
        const std::size_t size=l.size();
        const double* beg=l.begin();
        if (size>0)
        {
            x=beg[0];
            if (size>1)
                y=beg[1];
        }
        return *this;
    }

    Point2D & Point2D::operator = (const std::vector<double>& l) noexcept
    {
        const std::size_t size = l.size();
        const double* beg = &(*l.begin());
        if (size>0)
        {
            x=beg[0];
            if (size>1)
                y=beg[1];
        }
        return *this;
    }

    Point2D & Point2D::operator += (const Vec2& target) noexcept
    {
        x+=target.x;
        y+=target.y;
        return *this;
    }

    Point2D Point2D::operator + (const Vec2& target) const noexcept
    {
        return std::move(Point2D(x+target.x,y+target.y));
    }

    Point2D & Point2D::operator -= (const Vec2& target) noexcept
    {
        x-=target.x;
        y-=target.y;
        return *this;
    }

    Vec2 Point2D::operator - (const Point2D& target) const noexcept
    {
        return std::move(Vec2(x-target.x,y-target.y));
    }

    Point2D Point2D::operator - (const Vec2& target) const noexcept
    {
        return std::move(Point2D(x-target.x,y-target.y));
    }

    Point2D Point2D::operator - () const noexcept
    {
        return std::move(Point2D(-x,-y));
    }

    Point2D & Point2D::operator *= (const double& a) noexcept
    {
        x*=a;
        y*=a;
        return *this;
    }

    Point2D Point2D::operator * (const double& a) const noexcept
    {
        return std::move(Point2D(x*a,y*a));
    }

    Point2D & Point2D::operator /= (const double& a) noexcept
    {
        x/=a;
        y/=a;
        return *this;
    }
    Point2D Point2D::operator / (const double& a) const noexcept
    {
        return std::move(Point2D(x/a,y/a));
    }


    Point2D::operator Vec2() const noexcept
    {
        return Vec2(x,y);
    }

    Vec2 Point2D::v2() const noexcept
    {
        return Vec2(x,y);
    }

    Point2D::Point2D() noexcept: x(0), y(0){/**/}

    Point2D::Point2D(const Vec2& a) noexcept: x(a.x), y(a.y){/**/}

    Point2D::Point2D(const double& _x,const double& _y) noexcept: x(_x), y(_y){/**/}

    Point2D::Point2D(const std::initializer_list<double>& l) noexcept
    {
        const std::size_t size = l.size();
        const double* beg = l.begin();
        if (size>0)
        {
            x = beg[0];
            if (size>1)
                y = beg[1];
        }
    }

    Point2D::Point2D(const std::vector<double>& l) noexcept
    {
        const std::size_t size = l.size();
        const double* beg = &(*l.begin());
        if (size>0)
        {
            x=beg[0];
            if (size>1)
                y=beg[1];
        }
    }


    ///--------------------------------------------------------------------------------------------

    double Point3D::dist(const Point3D& target)const noexcept
    {
        return sqrt(pow(x-target.x,2)+pow(y-target.y,2)+pow(z-target.z,2));
    }

    void Point3D::round(const unsigned int& a) noexcept
    {
        const unsigned int p = pow(10,a);
        x = std::round(x*p) / p;
        if (x==-0.0d)
            x=0;
        y = std::round(y*p) / p;
        if (y==-0.0d)
            y=0;
        z = std::round(z*p) / p;
        if (z==-0.0d)
            z=0;
    }

    bool Point3D::operator == (const Point3D& target) const noexcept
    {
        return x == target.x && y == target.y && z == target.z;
    }

    bool Point3D::operator != (const Point3D& target) const noexcept
    {
        return x != target.x || y != target.y || z != target.z;
    }

    Point3D & Point3D::operator = (const std::initializer_list<double>& l) noexcept
    {
        const std::size_t size=l.size();
        const double* beg=l.begin();
        if (size>0)
        {
            x=beg[0];
            if (size>1)
            {
                y=beg[1];
                if (size>2)
                    z=beg[2];
            }
        }
        return *this;
    }

    Point3D & Point3D::operator = (const std::vector<double>& l) noexcept
    {
        const std::size_t size = l.size();
        const double* beg = &(*l.begin());
        if (size>0)
        {
            x=beg[0];
            if (size>1)
            {
                y=beg[1];
                if (size>2)
                    z=beg[2];
            }
        }
        return *this;
    }

    Point3D & Point3D::operator += (const Vec3& target) noexcept
    {
        x+=target.x;
        y+=target.y;
        z+=target.z;
        return *this;
    }

    Point3D Point3D::operator + (const Vec3& target) const noexcept
    {
        return std::move(Point3D(x+target.x,y+target.y,z+target.z));
    }

    Point3D & Point3D::operator -= (const Vec3& target) noexcept
    {
        x-=target.x;
        y-=target.y;
        z-=target.z;
        return *this;
    }

    Vec3 Point3D::operator - (const Point3D& target) const noexcept
    {
        return Vec3(x-target.x,y-target.y,z-target.z);
    }

    Point3D Point3D::operator - (const Vec3& target) const noexcept
    {
        return std::move(Point3D(x-target.x,y-target.y,z-target.z));
    }

    Point3D Point3D::operator - () const noexcept
    {
        return std::move(Point3D(-x,-y,-z));
    }

    Point3D & Point3D::operator *= (const double& a) noexcept
    {
        x*=a;
        y*=a;
        z*=a;
        return *this;
    }

    Point3D Point3D::operator * (const double& a) const noexcept
    {
        return std::move(Point3D(x*a,y*a,z*a));
    }

    Point3D & Point3D::operator /= (const double& a) noexcept
    {
        x/=a;
        y/=a;
        z/=a;
        return *this;
    }

    Point3D Point3D::operator / (const double& a) const noexcept
    {
        return std::move(Point3D(x/a,y/a,z/a));
    }

    Point3D::operator Vec3() const noexcept
    {
        return Vec3(x,y,z);
    }

    Vec3 Point3D::v3() const noexcept
    {
        return Vec3(x,y,z);
    }

    Point3D::Point3D() noexcept :Point2D()
    {
        z=0;
    }

    Point3D::Point3D(const Vec3& target) noexcept
    {
        x=target.x;
        y=target.y;
        z=target.z;
    }

    Point3D::Point3D(const double& _x,const double& _y,const double& _z) noexcept :Point2D(_x,_y)
    {
        z=_z;
    }

    Point3D::Point3D(const std::initializer_list<double>& l) noexcept
    {
        const std::size_t size=l.size();
        const double* beg=l.begin();
        if (size>0)
        {
            x=beg[0];
            if (size>1)
            {
                y=beg[1];
                if (size>2)
                    z=beg[2];
            }
        }
    }

    Point3D::Point3D(const std::vector<double>& l) noexcept
    {
        const std::size_t size = l.size();
        const double* beg = &(*l.begin());
        if (size>0)
        {
            x=beg[0];
            if (size>1)
            {
                y=beg[1];
                if (size>2)
                    z=beg[2];
            }
        }
    }

    std::ostream& operator << (std::ostream& stream,const Point2D& a)
    {
        return stream << "(" << a.x << "," << a.y << ")";
    }
    std::ostream& operator << (std::ostream& stream,const Point3D& a)
    {
        return stream << "(" << a.x << "," << a.y << "," << a.z << ")";
    }

}

//
